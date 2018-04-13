#include <iostream>
#include <map>
#include <unordered_map>

#include <exception>

#include "performance_test_helper.h"

int main()
{
    performance_test<std::map<std::string, int>, Size::SMALL,  Case::RANDOM,  Length::SHORT>("map");
    performance_test<std::map<std::string, int>, Size::MEDIUM, Case::RANDOM,  Length::SHORT>("map");
    performance_test<std::map<std::string, int>, Size::LARGE,  Case::RANDOM,  Length::SHORT>("map");
    performance_test<std::map<std::string, int>, Size::SMALL,  Case::SIMILAR, Length::SHORT>("map");
    performance_test<std::map<std::string, int>, Size::MEDIUM, Case::SIMILAR, Length::SHORT>("map");
    performance_test<std::map<std::string, int>, Size::LARGE,  Case::SIMILAR, Length::SHORT>("map");

    performance_test<std::map<std::string, int>, Size::SMALL,  Case::RANDOM,  Length::LONG >("map");
    performance_test<std::map<std::string, int>, Size::MEDIUM, Case::RANDOM,  Length::LONG >("map");
    performance_test<std::map<std::string, int>, Size::LARGE,  Case::RANDOM,  Length::LONG >("map");
    performance_test<std::map<std::string, int>, Size::SMALL,  Case::SIMILAR, Length::LONG >("map");
    performance_test<std::map<std::string, int>, Size::MEDIUM, Case::SIMILAR, Length::LONG >("map");
    performance_test<std::map<std::string, int>, Size::LARGE,  Case::SIMILAR, Length::LONG >("map");


    performance_test<std::unordered_map<std::string, int>, Size::SMALL,  Case::RANDOM,  Length::SHORT>("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::MEDIUM, Case::RANDOM,  Length::SHORT>("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::LARGE,  Case::RANDOM,  Length::SHORT>("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::SMALL,  Case::SIMILAR, Length::SHORT>("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::MEDIUM, Case::SIMILAR, Length::SHORT>("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::LARGE,  Case::SIMILAR, Length::SHORT>("unordered_map");

    performance_test<std::unordered_map<std::string, int>, Size::SMALL,  Case::RANDOM,  Length::LONG >("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::MEDIUM, Case::RANDOM,  Length::LONG >("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::LARGE,  Case::RANDOM,  Length::LONG >("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::SMALL,  Case::SIMILAR, Length::LONG >("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::MEDIUM, Case::SIMILAR, Length::LONG >("unordered_map");
    performance_test<std::unordered_map<std::string, int>, Size::LARGE,  Case::SIMILAR, Length::LONG >("unordered_map");
}
