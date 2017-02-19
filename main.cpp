#include <string>

#include "prefix_tree.h"

int main()
{
    //test();
    local::prefix_tree<std::string, int> a;
    local::prefix_tree<std::string, int> b(a);
    local::prefix_tree<std::string, int> c = { {"one", 1}, {"two", 2} };
}
