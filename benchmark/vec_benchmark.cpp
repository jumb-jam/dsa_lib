#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "ds/vector.hpp"

using namespace std::chrono;

constexpr std::size_t INT_N    = 10'000'000;
constexpr std::size_t STRING_N = 1'000'000;
constexpr std::size_t LARGE_N  = 1'000'000;

struct Large
{
    int data[64]{};
};

template<typename Vec>
void benchmark_int_push(const char* name, bool reserve)
{
    auto start = high_resolution_clock::now();

    Vec v;

    if (reserve)
        v.reserve(INT_N);

    for (std::size_t i = 0; i < INT_N; ++i)
        v.push_back(static_cast<int>(i));

    volatile long long sum = 0;

    for (auto x : v)
        sum += x;

    auto end = high_resolution_clock::now();

    std::cout << name
              << (reserve ? " [reserve]" : " [no reserve]")
              << " : "
              << duration_cast<milliseconds>(end - start).count()
              << " ms\n";

    std::cout << "sum = " << sum << "\n\n";
}

template<typename Vec>
void benchmark_string_push(const char* name, bool reserve)
{
    auto start = high_resolution_clock::now();

    Vec v;

    if (reserve)
        v.reserve(STRING_N);

    for (std::size_t i = 0; i < STRING_N; ++i)
        v.push_back(std::to_string(i));

    volatile std::size_t sum = 0;

    for (const auto& s : v)
        sum += s.size();

    auto end = high_resolution_clock::now();

    std::cout << name
              << (reserve ? " [reserve]" : " [no reserve]")
              << " : "
              << duration_cast<milliseconds>(end - start).count()
              << " ms\n";

    std::cout << "string chars = " << sum << "\n\n";
}

template<typename Vec>
void benchmark_large_push(const char* name, bool reserve)
{
    auto start = high_resolution_clock::now();

    Vec v;

    if (reserve)
        v.reserve(LARGE_N);

    for (std::size_t i = 0; i < LARGE_N; ++i)
        v.push_back(Large{});

    volatile long long sum = 0;

    for (const auto& x : v)
        sum += x.data[0];

    auto end = high_resolution_clock::now();

    std::cout << name
              << (reserve ? " [reserve]" : " [no reserve]")
              << " : "
              << duration_cast<milliseconds>(end - start).count()
              << " ms\n";

    std::cout << "sum = " << sum << "\n\n";
}

template<typename Vec>
void benchmark_copy(const char* name)
{
    Vec v;
    v.reserve(INT_N);

    for (std::size_t i = 0; i < INT_N; ++i)
        v.push_back(static_cast<int>(i));

    auto start = high_resolution_clock::now();

    Vec copy = v;

    auto end = high_resolution_clock::now();

    volatile auto s = copy.size();
    (void)s;

    std::cout << name
              << " copy ctor : "
              << duration_cast<milliseconds>(end - start).count()
              << " ms\n\n";
}

template<typename Vec>
void benchmark_move(const char* name)
{
    Vec v;
    v.reserve(INT_N);

    for (std::size_t i = 0; i < INT_N; ++i)
        v.push_back(static_cast<int>(i));

    auto start = high_resolution_clock::now();

    Vec moved = std::move(v);

    auto end = high_resolution_clock::now();

    volatile auto s = moved.size();
    (void)s;

    std::cout << name
              << " move ctor : "
              << duration_cast<milliseconds>(end - start).count()
              << " ms\n\n";
}

int main()
{
    std::cout << "========== INT ==========\n\n";

    benchmark_int_push<dsa::Vector<int>>("Your Vector", false);
    benchmark_int_push<std::vector<int>>("std::vector", false);

    benchmark_int_push<dsa::Vector<int>>("Your Vector", true);
    benchmark_int_push<std::vector<int>>("std::vector", true);

    std::cout << "\n========== STRING ==========\n\n";

    benchmark_string_push<dsa::Vector<std::string>>("Your Vector", false);
    benchmark_string_push<std::vector<std::string>>("std::vector", false);

    benchmark_string_push<dsa::Vector<std::string>>("Your Vector", true);
    benchmark_string_push<std::vector<std::string>>("std::vector", true);

    std::cout << "\n========== LARGE STRUCT ==========\n\n";

    benchmark_large_push<dsa::Vector<Large>>("Your Vector", false);
    benchmark_large_push<std::vector<Large>>("std::vector", false);

    benchmark_large_push<dsa::Vector<Large>>("Your Vector", true);
    benchmark_large_push<std::vector<Large>>("std::vector", true);

    std::cout << "\n========== COPY ==========\n\n";

    benchmark_copy<dsa::Vector<int>>("Your Vector");
    benchmark_copy<std::vector<int>>("std::vector");

    std::cout << "\n========== MOVE ==========\n\n";

    benchmark_move<dsa::Vector<int>>("Your Vector");
    benchmark_move<std::vector<int>>("std::vector");
}