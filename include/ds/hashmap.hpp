#pragma once

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <utility>

namespace dsa{

template <typename Key, typename Value>
class HashMap{
private:

    struct Bucket{
        Key key;
        Value value;

        bool occupied;
        bool deleted;
    }

    Bucket* data_;

    std::size_t size_;
    std::size_t capacity_;
public:
};
}