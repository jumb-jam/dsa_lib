#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>

#include <ds/vector.hpp>

namespace dsa{

template <typename T>

class Stack{
private:
    Vector<T> data;

public:
    
    void push(const T& value){
        data.push_back(value);
    }

    void pop(){
        if(data.isempty()){
            throw std::out_of_range("stack is empty");
        }
        data.pop_back();
    }

    T& top(){
        return data.back();
    }

    const T& top() const {
        return data.back();
    }

    bool isempty() const {
        return data.isempty();
    }

    std::size_t size() const {
        return data.size();
    }

};
}