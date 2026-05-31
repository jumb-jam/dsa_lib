#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>


namespace dsa{

template <typename T>

class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void resize_capacity(std::size_t newCap) {
        T* newData = new T[newCap];

        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
    }

public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}  //constructors
    Vector(std::size_t n) : data_(new T[n] {}), size_(n), capacity_(n){}

    ~Vector() { //destructor
        delete[] data_;
        size_= 0;
        capacity_= 0;
    }

    Vector(const Vector& v) : data_(new T[v.capacity_] {}), size_(v.size_), capacity_(v.capacity_) { //copy constructor
        for(std::size_t i=0;i<size_;i++){
            data_[i]=v.data_[i];
        }
    }

    Vector& operator=(const Vector& v){ //copy assignment
        if(this == &v){
            return *this;
        }

        delete[] data_;

        size_=v.size_;
        capacity_=v.capacity_;

        data_= new T[capacity_];

        for(std::size_t i=0;i<size_;i++){
            data_[i]=v.data_[i];
        }

        return *this;
    }

    Vector(Vector&& v) noexcept : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {//move constructor

        v.data_=nullptr;
        v.size_=0;
        v.capacity_=0;
        
    }

    Vector& operator=(Vector&& v) noexcept { //move assignment
        if(this == &v){
            return *this;
        }

        delete[] data_;

        data_=v.data_;
        size_=v.size_;
        capacity_=v.capacity_;

        v.data_= nullptr;
        v.size_= 0;
        v.capacity_= 0;

        return *this;

    }



    std::size_t size() const{
        return size_;
    }
    std::size_t capacity() const{
        return capacity_;
    }

    bool isempty() const{
        return size_ == 0 ;
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }
    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    void push_back(const T& value) {    
        if(size_ == capacity_){
            resize_capacity( capacity_ == 0 ? 1 : capacity_*2);
        }
        data_[size_] = value;
        size_++;
    }

    void pop_back() {
        if(size_ > 0){
            size_--;
        }
        else{
            return;
        }
    }

    void resize(std::size_t new_size){
        if(new_size > capacity_){
            std::size_t new_cap = (capacity_ == 0) ? 1 : capacity_;

            while (new_cap < new_size) {
                new_cap *= 2;
            }

            resize_capacity(new_cap);
        }
        if (new_size > size_) {
            for (std::size_t i = size_; i < new_size; ++i) {
                data_[i] = T{};
            }
        }

        size_ = new_size;
    }

    void insert(std::size_t index, const T& value){
        if(index > size_){
            throw std::out_of_range("index out of range");
        }

        if(size_ == capacity_){
            resize_capacity(capacity_ == 0 ? 1 : capacity_*2);
        }

        for (std::size_t i = size_;i > index;--i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        size_++;
    }

    void erase(std::size_t index){
        if(index>=size_){
            throw std::out_of_range("Index out of range");
        }

        for (std::size_t i = index; i < size_ - 1; i++) {
            data_[i]=data_[i + 1];
        }
        size_--;
    }

    T& at(std::size_t index){
        if(index >= size_){
            throw std::out_of_range("Index out of range");
        }

        return data_[index];
    }

    const T& at(std::size_t index) const {
        if(index >= size_){
            throw std::out_of_range("Index out of range");
        }

        return data_[index];
    }

    T& front(){
        assert(size_ > 0);
        return data_[0];
    }

    const T& front() const {
        assert(size_ > 0);
        return data_[0];
    }

    T& back(){
        assert(size_ > 0);
        return data_[size_ - 1];
    }

    const T& back() const {
        assert(size_ > 0);
        return data_[size_ - 1];
    }

    void reserve(std::size_t newCap){
        if(capacity_ <= newCap){
            resize_capacity(newCap);
        }
    }

    void shrink_to_fit(){
        if(size_ < capacity_){
            resize_capacity(size_);
        }
    }

    T* begin(){
        return data_;
    }

    T* end(){
        return data_ + size_;
    }

    const T* begin() const {
        return data_;
    }

    const T* end() const{
        return data_ + size_;
    }

    void clear(){
        size_ = 0;
    }

    

    

};

}