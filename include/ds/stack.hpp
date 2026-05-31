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
    Vector<T> stack;

public:
    
    void push(const T& value){
        stack.push_back(value);
    }

    void pop(){
        if(stack.isempty()){
            throw std::out_of_range("stack is empty");
        }
        stack.pop_back();
    }

    T& top(){
        return stack.back();
    }

    const T& top() const {
        return stack.back();
    }

    bool isempty() const {
        return stack.isempty();
    }

    std::size_t size() const {
        return stack.size_();
    }

};
}