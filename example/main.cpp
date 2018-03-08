#include <iostream>
#include <string>

#include <prefix_tree.h>

/*
 * Container is an associative STL compatible one,
 * so the usage is pretty much the same as of an
 * std::map or std::unordered_map.
 */

int main()
{
    // Creating an object
    local::prefix_tree<std::string, int> pt;
    local::prefix_tree<std::string, int> pt2{
        { "one", 1 },
        { "two", 2 },
        { "three", 3},
        { "four", 4}
    };
    local::prefix_tree<std::string, int> pt3(pt2);
    local::prefix_tree<std::string, int> pt4(pt3.begin(), pt3.end());
    pt = p4;

    // Selectors
    auto findOne = pt.find("one");
    auto findNine = pt.find("nine");

}
