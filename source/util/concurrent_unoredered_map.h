//
// Created by vladimira on 11/05/2024.
//

#ifndef VOXEL_CONCURRENT_UNORDERED_MAP_H
#define VOXEL_CONCURRENT_UNORDERED_MAP_H

#include <unordered_map>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <stdexcept>

/*!
@brief namespace for JongYoon Lim
@see https://github.com/lime62
*/
namespace lime62 {
    /*!
    @brief A simple C++11 Concurrent Queue based on std::queue.

     Supports waiting operations for retrieving an element when it's empty.
     It's interrupted by calling interrupt().

    @ref std::queue class
    */
    template<typename T, typename U,
            typename _Hash = std::hash<T>,
            typename _Pred = std::equal_to<T>,
            typename _Alloc = std::allocator<std::pair<const T, U>>>
    class concurrent_unordered_map {
    public:
        typedef std::__umap_hashtable<T, U, _Hash, _Pred, _Alloc>  _Hashtable;
        _Hashtable _M_h;

        typedef typename std::unordered_map<T,U>::size_type size_type;
        typedef typename std::unordered_map<T,U>::reference reference;
        typedef typename _Hashtable::iterator		iterator;

        ~concurrent_unordered_map() {
            interrupt();
        }

        void interrupt() {
            interrupted_ = true;
            condition_variable_.notify_one();
        }

        U& operator[](T const& k){
            std::unique_lock<std::mutex> lock(mutex_);
            return map_[k];
        }

        void insert(T const& key, U const& val){
            {
                std::unique_lock<std::mutex> lock(mutex_);
                map_[key] = val;
            }
            condition_variable_.notify_one();
        }

        iterator find(T const& key){
            std::unique_lock<std::mutex> lock(mutex_);
            return map_.find(key);
        }

        template<typename... _Args>
        void emplace(_Args&&... __args) {
            {
                std::unique_lock<std::mutex> lock(this->mutex_);
                map_.emplace(std::forward<_Args>(__args)...);
            }
            condition_variable_.notify_one();
        }

        bool empty() {
            std::unique_lock<std::mutex> lock(this->mutex_);
            return map_.empty();
        }

        void remove(T const& key){
            std::unique_lock<std::mutex> lock(this->mutex_);
            if (map_.find(key) != map_.end())
                map_.erase(key);
        }

        size_type size() const {
            std::unique_lock<std::mutex> lock(this->mutex_);
            return map_.size();
        }

        void clear(){
            std::unique_lock<std::mutex> lock(this->mutex_);
            map_.clear();
        }

        iterator begin(){
            return map_.begin();
        }

        iterator end(){
            return map_.end();
        }

        /*bool operator!=(const concurrent_unordered_map<T,U>& other){
            return this->size() != other.size();
        }*/

        void lock(){
            mutex_.lock();
        }

        void unlock(){
            mutex_.unlock();
        }

    protected:
        std::unordered_map<T, U> map_;
        std::mutex mutex_;
        std::condition_variable condition_variable_;
        std::atomic_bool interrupted_;
    };
}

#endif //VOXEL_CONCURRENT_UNORDERED_MAP_H
