#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include <prefix_tree.h>

#include "time_tracker.h"

enum class Size : char
{
    SMALL,   // 100
    MEDIUM,  // 10000
    LARGE    // 300000
};

std::string to_string(const Size s)
{
    switch (s) {
    case Size::SMALL:
        return "SMALL";
    case Size::MEDIUM:
        return "MEDIUM";
    case Size::LARGE:
        return "LARGE";
    }
    return std::string();
}

constexpr int get_size(const Size s)
{
    switch (s) {
    case Size::SMALL:
        return 100;
    case Size::MEDIUM:
        return 10000;
    case Size::LARGE:
        return 300000;
    }
    return 100;
}

enum class Case : char
{
    RANDOM,
    SIMILAR
};

std::string to_string(const Case s)
{
    switch (s) {
    case Case::RANDOM:
        return "RANDOM";
    case Case::SIMILAR:
        return "SIMILAR";
    }
    return std::string();
}

enum class Length : char
{
    SHORT,
    LONG
};

std::string to_string(const Length s)
{
    switch (s) {
    case Length::SHORT:
        return "SHORT";
    case Length::LONG:
        return "LONG";
    }
    return std::string();
}

std::pair<int, int> get_length(const Length l)
{
    switch (l) {
    case Length::SHORT:
        return { 8, 4 };
    case Length::LONG:
        return { 128, 96 };
    }
    return { 8, 4 };
}

template <Case C>
char generate_character(int i)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<char> dis('!', '~');
    return dis(gen);
}

template <>
char generate_character<Case::SIMILAR>(int i)
{
    return '!' + i % ('~' - '!');
}

template <Case C, Length L>
std::string generate_key()
{
    std::string result;
    const auto lengths = get_length(L);
    result.reserve(lengths.first);
    for (int i = 0; i < lengths.second; ++i) {
        result.push_back(generate_character<C>(i));
    }
    for (int i = lengths.second; i < lengths.first; ++i) {
        result.push_back(generate_character<Case::RANDOM>(i));
    }
    return result;
}

template <typename ContainerT,
          Size S,
          Case C,
          Length L>
void performance_test(const std::string& against)
{
    std::cout << "===========================\n";
    std::cout << to_string(S) << '\t' << to_string(C) << '\t' << to_string(L) << '\n';

    local::prefix_tree<std::string, int> src;
    ContainerT dst;
    time_tracker src_tracker("prefix_tree");
    time_tracker dst_tracker(against);
    std::vector<std::string> keys;

    // Insert
    for (int i = 0; i < get_size(S); ++i) {
        const auto key = generate_key<C, L>();
        keys.push_back(key);
        src.insert({ key, i });
        dst.insert({ key, i });
    }

    // Find
    std::cout << "Testing find\n";
    for (int i = 0; i < get_size(S) / 10; ++i) {
        std::string key = generate_key<Case::RANDOM, Length::SHORT>();

        src_tracker.start();
        src.find(key);
        src_tracker.end();

        dst_tracker.start();
        dst.find(key);
        dst_tracker.end();
    }
    src_tracker.print_compare(dst_tracker);
    src_tracker.reset();
    dst_tracker.reset();
}
