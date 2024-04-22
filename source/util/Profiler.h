//
// Created by Alienso on 27.4.2023..
//

#ifndef GRASSTERRAIN_PROFILER_H
#define GRASSTERRAIN_PROFILER_H


#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>

#define PROFILING 0

#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name);
#else
#define PROFILE_SCOPE(name)
#endif

struct ProfileResult{
    ProfileResult(std::string _name, long long _start, long long _end) : name(std::move(_name)), start(_start), end(_end){}
    std::string name;
    long long start,end;
};

struct InstrumentationSession{
    explicit InstrumentationSession(std::string  _name) : name(std::move(_name)){}
    std::string name;
};

class Instrumentor {
public:
    Instrumentor();

    void beginSession(const std::string& name, const std::string& filepath = "results.json");
    void endSession();

    void writeProfile(const ProfileResult& result);
    void writeHeader();
    void writeFooter();

    static Instrumentor& get();

private:
    InstrumentationSession* currentSession;
    std::ofstream outputStream;
    int profileCount;
};

class InstrumentationTimer {
public:
    explicit InstrumentationTimer(const char* _name);
    ~InstrumentationTimer();

    void stop();

private:
    const char* name;
    std::chrono::time_point<std::chrono::steady_clock> startTimePoint;
    bool stopped;
};


#endif //GRASSTERRAIN_PROFILER_H
