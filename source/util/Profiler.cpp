//
// Created by Alienso on 27.4.2023..
//

#include "Profiler.h"

Instrumentor::Instrumentor() : currentSession(nullptr), profileCount(0) {}

void Instrumentor::beginSession(const std::string& name, const std::string& filepath){
    outputStream.open(filepath);
    writeHeader();
    currentSession = new InstrumentationSession{ name };
}

void Instrumentor::endSession(){
    writeFooter();
    outputStream.close();
    delete currentSession;
    currentSession = nullptr;
    profileCount = 0;
}

void Instrumentor::writeProfile(const ProfileResult& result){
    if (profileCount++ > 0)
        outputStream << ",";

    std::string name = result.name;
    std::replace(name.begin(), name.end(), '"', '\'');

    outputStream << "{";
    outputStream << R"("cat":"function",)";
    outputStream << "\"dur\":" << (result.end - result.start) << ',';
    outputStream << R"("name":")" << name << "\",";
    outputStream << R"("ph":"X",)";
    outputStream << "\"pid\":0,";
    outputStream << "\"tid\":" << 0 << ",";
    outputStream << "\"ts\":" << result.start;
    outputStream << "}";

    outputStream.flush();
}

void Instrumentor::writeHeader(){
    outputStream << R"({"otherData": {},"traceEvents":[)";
    outputStream.flush();
}

void Instrumentor::writeFooter(){
    outputStream << "]}";
    outputStream.flush();
}

Instrumentor& Instrumentor::get(){
    static Instrumentor instance;
    return instance;
}



InstrumentationTimer::InstrumentationTimer(const char* _name) : name(_name), stopped(false) {
    startTimePoint = std::chrono::steady_clock::now();
}

InstrumentationTimer::~InstrumentationTimer(){
    if (!stopped) stop();
}

void InstrumentationTimer::stop(){
    auto endTimePoint = std::chrono::steady_clock::now();

    long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
    long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

    Instrumentor::get().writeProfile({name,start,end});

    stopped = true;
}