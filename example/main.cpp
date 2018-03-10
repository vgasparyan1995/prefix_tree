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
    pt = pt4;

    // Selectors
    auto iter_to_one = pt.find("one");
    if (iter_to_one != pt.end()) {
        std::cout << "One exists.\n";
    }
    auto size = pt.size();
    std::cout << "Size is: " << size << '\n';
    auto is_empty = pt.empty();
    std::cout << "Container is " << (is_empty ? "empty" : "not empty") << '\n';

    // Mutators
    auto insertion_result = pt.insert({ "five", 5 });
    auto insertion_result2 = pt.insert("six", 6);
    auto ref_to_six = pt["six"];
    auto ref_to_new_seven = pt["seven"];
    ref_to_new_seven = ref_to_six;
    std::cout << "Six: " << pt["six"] << '\n';
    std::cout << "Seven: " << pt["seven"] << '\n';
    pt.erase("six");
    pt.erase(iter_to_one);
}
