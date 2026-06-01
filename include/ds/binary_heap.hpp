#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <functional>

#include <ds/vector.hpp>

namespace dsa{

template <typename T, typename Compare = std::less<T>>

class Heap{
private:
    Vector<T> data_;
    Compare comp_;

    void heapify_up(std::size_t index){
        while(index > 0){

            std::size_t parent= (index - 1)/2;

            if(comp_(data_[index],data_[parent])){
                std::swap(data_[index],data_[parent]);
                index=parent;
                continue;
            }

            break;
            
        }
    }

    void heapify_down(std::size_t index){
        while (true) {

            std::size_t left = 2*index + 1;
            std::size_t right = 2*index + 2;

            std::size_t smallest = index;

            if (left < data_.size() && comp_(data_[left],data_[smallest])) {
                smallest = left;
            }

            if (right < data_.size() && comp_(data_[right],data_[smallest])) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            std::swap(data_[index], data_[smallest]);
            index = smallest;
        }
    }

public:

    void push(const T& value){
        data_.push_back(value);

        heapify_up(data_.size() - 1);
    }

    void pop(){
        if (data_.isempty()) {
            throw std::out_of_range("heap is empty");
        }

        std::swap(data_[0],data_[data_.size() - 1]);
        data_.pop_back();

        if(!data_.isempty()){
            heapify_down(0);
        }
    }

    const T& top() const {
        if (data_.isempty()) {
            throw std::out_of_range("heap is empty");
        }

        return data_[0];
    }

    std::size_t size() const {
        return data_.size();
    }

    bool isempty() const {
        return data_.isempty();
    }

};
}