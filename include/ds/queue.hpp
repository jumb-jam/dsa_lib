#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <utility>

#include <ds/deque.hpp>

namespace dsa{

template <typename T>

class Queue{
private:
    Deque<T> queue;

public:
    void enqueue(const T& value){
        queue.push_back(value);
    }

    void dequeue(){
        queue.pop_front();
    }

    T& front(){
        return queue.front();
    }

    const T& front() const {
        return queue.front();
    }

    const T& back() const {
        return queue.back();
    }

    std::size_t size() const {
        return queue.size();
    }

    bool isempty() const {
        return queue.isempty();
    }
};

}