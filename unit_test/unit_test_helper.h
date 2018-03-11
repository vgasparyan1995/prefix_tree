#pragma once

#include <iostream>
#include <string>

#define BEGIN_TEST_GROUP(group_name)\
    {\
        const std::string k_group_name = #group_name;\
        int total_counter = 0;\
        int fail_counter = 0;\
        std::cout << "Testing \"" << k_group_name << "\"\n";

#define END_TEST_GROUP()\
        std::cout << "Done testing \"" << k_group_name << "\"\n";\
        std::cout << "\ttotal: " << total_counter <<\
                     " passed: " << (total_counter - fail_counter) <<\
                     " failed: " << fail_counter << "\n";\
    }

#define TEST(bool_expr, ID)\
    if ((bool_expr)) {\
        std::cout << "_passed_";\
    } else {\
        std::cout << "_FAILED_";\
        ++fail_counter;\
    }\
    std::cout << ' ' << #ID << '\n';\
    ++total_counter;

