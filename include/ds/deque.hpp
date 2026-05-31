#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <utility>

namespace dsa{

template <typename T>

class Deque{
private:
    T* data_;

    std::size_t size_;
    std::size_t capacity_;

    std::size_t front_;
    std::size_t back_;

    void resize_capacity(std::size_t newCap){
        T* newData = new T[newCap];

        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[(front_ + i) % capacity_]);
        }

        delete[] data_;

        data_=newData;
        capacity_=newCap;

        if(size_ == 0){
            front_=0;
            back_=0;
        }
        else{
            front_=0;
            back_=size_-1;
        }
    }

public:

    Deque() : data_(nullptr), size_(0), capacity_(0), front_(0), back_(0) {}

    ~Deque() {
        delete[] data_;
        size_=0;
        capacity_=0;

        front_=0;
        back_=0;
    }

    Deque(const Deque& d) : data_(new T[d.capacity_] {}),           //copy constructor
                            size_(d.size_),
                            capacity_(d.capacity_)
    { 
        for(std::size_t i=0;i<size_;i++){
            data_[i]=d.data_[(d.front_ + i) % d.capacity_];
        }

        front_=0;
        back_= (size_ == 0) ? 0 : size_ - 1;
    }

    Deque& operator=(const Deque& d){ //copy assignment
        if(this == &d){
            return *this;
        }

        delete[] data_;

        size_=d.size_;
        capacity_=d.capacity_;

        data_= new T[capacity_];

        for(std::size_t i=0;i<size_;i++){
            data_[i]=d.data_[(d.front_ + i) % d.capacity_];
        }

        front_=0;
        back_= (size_ == 0) ? 0 : size_ - 1;

        return *this;
    }

    Deque(Deque&& d) noexcept : data_(d.data_),  //move constructor
                                size_(d.size_),
                                capacity_(d.capacity_),
                                front_(d.front_),
                                back_(d.back_)
    {

        d.data_=nullptr;
        d.size_=0;
        d.capacity_=0;

        d.front_=0;
        d.back_=0;
    }

    Deque& operator=(Deque&& d) noexcept{ //move assignment
        if(this == &d){
            return *this;
        }

        delete[] data_;

        data_=d.data_;
        size_=d.size_;
        capacity_=d.capacity_;
        front_=d.front_;
        back_=d.back_;

        d.data_= nullptr;
        d.size_= 0;
        d.capacity_= 0;
        d.front_=0;
        d.back_=0;

        return *this;
    }

    std::size_t size() const {
        return size_;
    }

    bool isempty() const {
        return size_ == 0;
    }

    T& front(){
        if(size_ == 0){
            throw std::out_of_range("deque is empty");
        }
        return data_[front_];
    }

    const T& front() const {
        if(size_ == 0){
            throw std::out_of_range("deque is empty");
        }
        return data_[front_];
    }

    T& back(){
        if(size_ == 0){
            throw std::out_of_range("deque is empty");
        }
        return data_[back_];
    }

    const T& back() const {
        if(size_ == 0){
            throw std::out_of_range("deque is empty");
        }
        return data_[back_];
    }

    void push_back(const T& value){
        if(size_ == capacity_){
            resize_capacity((capacity_ == 0) ? 1 : capacity_*2);
        }

        back_ = (back_ + 1) % capacity_;
        data_[back_]=value;
        size_++;
    }

    void push_front(const T& value){
        if(size_ == capacity_){
            resize_capacity((capacity_ == 0) ? 1 : capacity_*2);
        }

        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_]=value;
        size_++;
    }

    void pop_front(){
        if(size_ == 0){
            throw std::out_of_range("deque is empty");
        }

        front_ = (front_ + 1) % capacity_;
        size_--;
    }

    void pop_back(){
        if(size_ == 0){
            throw std::out_of_range("deque is empty");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        size_--;
    }


    T& operator[](std::size_t index){
        if(index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[(front_ + index) % capacity_];
    }

    const T& operator[](std::size_t index) const {
        if(index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[(front_ + index) % capacity_];
    }

};

}