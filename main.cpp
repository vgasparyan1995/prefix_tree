#include <string>
#include <utility>

#include "prefix_tree.h"

int main()
{
    local::prefix_tree<std::string, int> a;
    local::prefix_tree<std::string, int> b(a);
    local::prefix_tree<std::string, int> c = { {"one", 1}, {"two", 2} };
    //local::prefix_tree<std::string, int> d = std::move(c);
}
