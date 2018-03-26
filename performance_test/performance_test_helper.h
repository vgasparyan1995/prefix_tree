#include <iostream>
#include <map>
#include <unordered_map>

#include <prefix_tree.h>

enum class Size : char
{
    SMALL,   // 100
    MEDIUM,  // 10000
    LARGE    // 1000000
};

constexpr get_size(constexpr Size s)
{
    switch (s) {
    case Size::SMALL:
        return 100;
    case Size::MEDIUM:
        return 10000;
    case Size::LARGE:
        return 1000000;
    }
    return 100;
}

enum class Case : char
{
    RANDOM,
    SIMILAR
};

enum class Length : char
{
    SHORT,
    LONG
};

template <template <typename, typename> typename ContainerT,
          Size S,
          Case C,
          Length L>
void peformance_test(const std::string& against)
{
    local::prefix_tree<std::string, int> src;
    ContainerT<std::string, int> dst;
    TimeTracker src_tracker("prefix_tree");
    TimeTracker dst_tracker(against);
    std::vector<std::string> keys;

    // Insert
    std::cout << "Testing insert\n";
    for (int i = 0; i < get_size(S); ++i) {
        const auto key = generate_key<C, L>();
        keys.push_back(key);

        START(src_tracker);
        src.insert({ key, i });
        END(src_tracker);

        START(dst_tracker);
        dst.insert({ key, i });
        END(dst_tracker);
    }
    src_tracker.print_and_reset();
    dst_tracker.print_and_reset();

    // Find
    std::cout << "Testing find\n";
    for (int i = 0; i < get_size(S) / 10; ++i) {
        std::string key;
        if (i % 5 == 0) {
            key = generate_key<Case::RANDOM, L>();
        } else {
            key = keys[i];
        }

        START(src_tracker);
        src.find(key);
        END(src_tracker);

        START(dst_tracker);
        dst.find(key);
        END(dst_tracker);
    }
    src_tracker.print_and_reset();
    dst_tracker.print_and_reset();

    // Remove
    std::cout << "Testing remove\n";
    for (int i = 0; i < get_size(S) / 10; ++i) {
        const auto key = keys[i];

        START(src_tracker);
        src.find(key);
        END(src_tracker);

        START(dst_tracker);
        dst.find(key);
        END(dst_tracker);
    }
    src_tracker.print_and_reset();
    dst_tracker.print_and_reset();
}
