#include <cassert>
#include <iostream>
#include <utility>
#include <stdexcept>

#include "ds/vector.hpp"

using namespace dsa;

void test_constructor() {
    Vector<int> v;

    assert(v.size() == 0);
    assert(v.capacity() == 0);
    assert(v.isempty());
}

void test_push_back() {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    assert(v.size() == 3);

    assert(v[0] == 10);
    assert(v[1] == 20);
    assert(v[2] == 30);
}

void test_resize_growth() {
    Vector<int> v;

    for (int i = 0; i < 100; i++) {
        v.push_back(i);
    }

    assert(v.size() == 100);

    for (int i = 0; i < 100; i++) {
        assert(v[i] == i);
    }
}

void test_pop_back() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.pop_back();

    assert(v.size() == 2);

    assert(v[0] == 1);
    assert(v[1] == 2);
}

void test_insert_middle() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(3);

    v.insert(1, 2);

    assert(v.size() == 3);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
}

void test_insert_front() {
    Vector<int> v;

    v.push_back(2);
    v.push_back(3);

    v.insert(0, 1);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
}

void test_insert_end() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);

    v.insert(v.size(), 3);

    assert(v.size() == 3);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
}

void test_erase_middle() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.erase(1);

    assert(v.size() == 2);

    assert(v[0] == 1);
    assert(v[1] == 3);
}

void test_erase_front() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.erase(0);

    assert(v.size() == 2);

    assert(v[0] == 2);
    assert(v[1] == 3);
}

void test_erase_back() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    v.erase(2);

    assert(v.size() == 2);

    assert(v[0] == 1);
    assert(v[1] == 2);
}

void test_clear() {
    Vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    v.clear();

    assert(v.size() == 0);
    assert(v.isempty());
}

void test_copy_constructor() {
    Vector<int> a;

    a.push_back(10);
    a.push_back(20);

    Vector<int> b = a;

    assert(b.size() == 2);

    assert(b[0] == 10);
    assert(b[1] == 20);

    b[0] = 999;

    assert(a[0] == 10);
    assert(b[0] == 999);
}

void test_copy_assignment() {
    Vector<int> a;

    a.push_back(1);
    a.push_back(2);

    Vector<int> b;

    b = a;

    assert(b.size() == 2);

    assert(b[0] == 1);
    assert(b[1] == 2);

    b[0] = 100;

    assert(a[0] == 1);
    assert(b[0] == 100);
}

void test_move_constructor() {
    Vector<int> a;

    a.push_back(10);
    a.push_back(20);

    Vector<int> b = std::move(a);

    assert(b.size() == 2);

    assert(b[0] == 10);
    assert(b[1] == 20);
}

void test_move_assignment() {
    Vector<int> a;

    a.push_back(5);
    a.push_back(6);

    Vector<int> b;

    b = std::move(a);

    assert(b.size() == 2);

    assert(b[0] == 5);
    assert(b[1] == 6);
}

void test_reserve() {
    Vector<int> v;

    v.reserve(100);

    assert(v.capacity() >= 100);
    assert(v.size() == 0);

    v.push_back(1);
    v.push_back(2);

    assert(v[0] == 1);
    assert(v[1] == 2);
}

void test_reserve_does_not_shrink() {
    Vector<int> v;

    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    std::size_t old_capacity = v.capacity();

    v.reserve(5);

    assert(v.capacity() == old_capacity);
    assert(v.size() == 10);
}

void test_at_valid() {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);

    assert(v.at(0) == 10);
    assert(v.at(1) == 20);
}

void test_at_out_of_range() {
    Vector<int> v;

    try {
        v.at(0);
        assert(false);
    }
    catch (const std::out_of_range&) {
    }
}

void test_front() {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    assert(v.front() == 10);

    v.front() = 99;

    assert(v[0] == 99);
}

void test_back() {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    assert(v.back() == 30);

    v.back() = 99;

    assert(v[2] == 99);
}

void test_begin_end() {
    Vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    auto it = v.begin();

    assert(*it == 10);

    ++it;
    assert(*it == 20);

    ++it;
    assert(*it == 30);

    ++it;
    assert(it == v.end());
}

void test_range_for() {
    Vector<int> v;

    for (int i = 1; i <= 5; i++) {
        v.push_back(i);
    }

    int sum = 0;

    for (int x : v) {
        sum += x;
    }

    assert(sum == 15);
}

void test_iterator_modification() {
    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    for (auto it = v.begin(); it != v.end(); ++it) {
        *it *= 2;
    }

    assert(v[0] == 2);
    assert(v[1] == 4);
    assert(v[2] == 6);
}

void test_empty_begin_end() {
    Vector<int> v;

    assert(v.begin() == v.end());
}

void test_front_back_single_element() {
    Vector<int> v;

    v.push_back(42);

    assert(v.front() == 42);
    assert(v.back() == 42);

    v.front() = 10;

    assert(v.front() == 10);
    assert(v.back() == 10);
}

void test_reserve_then_many_pushes() {
    Vector<int> v;

    v.reserve(1000);

    auto cap = v.capacity();

    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }

    assert(v.capacity() == cap);

    for (int i = 0; i < 1000; ++i) {
        assert(v[i] == i);
    }
}

int main() {
    test_constructor();
    test_push_back();
    test_resize_growth();

    test_pop_back();

    test_insert_middle();
    test_insert_front();
    test_insert_end();

    test_erase_middle();
    test_erase_front();
    test_erase_back();

    test_clear();

    test_copy_constructor();
    test_copy_assignment();

    test_move_constructor();
    test_move_assignment();

    test_reserve();
    test_reserve_does_not_shrink();

    test_at_valid();
    test_at_out_of_range();

    test_front();
    test_back();

    test_begin_end();
    test_range_for();
    test_iterator_modification();

    test_empty_begin_end();

    test_front_back_single_element();
    test_reserve_then_many_pushes();

    std::cout << "All tests passed!\n";
}

