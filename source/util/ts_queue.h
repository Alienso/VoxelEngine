//
// Created by Alienson on 27.1.2024..
//

#ifndef WINTER_TSQUEUE_H
#define WINTER_TSQUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename T>
class ts_queue {
public:
    ts_queue() = default;
    ts_queue(const ts_queue&) = delete;
    ~ts_queue(){
        clear();
    }

    void push_front(const T& val){
        scoped_lock lock(mutex_);
        queue.push_front(val);
        cvEmpty.notify_one();
    }
    void push_back(const T& val){
        scoped_lock lock(mutex_);
        queue.push_back(val);
        cvEmpty.notify_one();
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        scoped_lock lock(mutex_);
        queue.emplace_back(std::forward<Args>(args)...);
        cvEmpty.notify_one();
    }

    template<typename... Args>
    void emplace_front(Args&&... args) {
        scoped_lock lock(mutex_);
        queue.emplace_front(std::forward<Args>(args)...);
        cvEmpty.notify_one();
    }

    T pop_front(){
        scoped_lock lock(mutex_);
        T val = std::move(queue.front());
        queue.pop_front();
        cvFull.notify_one();
        return val;
    }

    T pop_back(){
        scoped_lock lock(mutex_);
        T val = std::move(queue.back());
        queue.pop_back();
        cvFull.notify_one();
        return val;
    }

    T& front() {
        scoped_lock lock(mutex_);
        return queue.front();
    }

    T& back() {
        scoped_lock lock(mutex_);
        queue.back();
    }

    size_t size() {
        scoped_lock lock(mutex_);
        return queue.size();
    }


    bool empty() {
        scoped_lock lock(mutex_);
        return queue.empty();
    }

    void clear() {
        scoped_lock lock(mutex_);
        queue.clear();
    }

    void waitForEvent() {
        while(empty()){
            unique_lock<mutex> ul(mutexEmpty);
            cvEmpty.wait(ul);
        }
    }


private:
    deque<T> queue;
    mutex mutex_;

    mutex mutexEmpty;
    condition_variable cvEmpty;
    mutex mutexFull;
    condition_variable cvFull;
};

#endif //WINTER_TSQUEUE_H
