#include <string>
#include <iostream>
#include <utility>
#include <unordered_map>
#include <chrono>

#include "prefix_tree.h"

template <typename MSG_T>
void BOOL_TEST(const bool value, MSG_T&& msg)
{
    std::cout << msg;
    if (value) {
        std::cout << " PASSED." << std::endl;
    } else {
        std::cout << " FAILED." << std::endl;
    }
}

template <typename ContainerT>
void init(ContainerT& a)
{
    for (int i = 1; i < 50000; ++i) {
        a.insert({"yeqa_zrtuzibil/subzrtuzibil/" + std::to_string(i), 1});
    }
    for (int i = 1; i < 10000; ++i) {
        a.insert({"urish_zrtuzibil/subzrtuzibil/" + std::to_string(i), 1});
    }
    for (int i = 1; i < 10000; ++i) {
        a.insert({"urish_zrtuzibil/ayl_subzrtuzibil/" + std::to_string(i), 1});
    }
}

template <typename ContainerT>
void find1(ContainerT& a, const std::string& container_name)
{
    const auto start = std::chrono::high_resolution_clock::now();
    
    a.find("yeqa_zrtuzibil/subzrtuzibil/993");
    a.find("urish_zrtuzibil/subzrtuzibil/993");
    a.find("urish_zrtuzibil/ayl_subzrtuzibil/993");
    a.find("yeqa_zrtuzibil/subzrtuzibil/12");
    a.find("urish_zrtuzibil/subzrtuzibil/12");
    a.find("urish_zrtuzibil/ayl_subzrtuzibil/12");
    a.find("yeqa_zrtuzibil/subzrtuzibil/13");
    a.find("urish_zrtuzibil/subzrtuzibil/13");
    a.find("urish_zrtuzibil/ayl_subzrtuzibil/13");

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time passed on find with " << container_name << " container: " << std::chrono::duration<double>(end - start).count() << " s.\n";
}

template <typename ContainerT>
void find2(ContainerT& a, const std::string& container_name)
{
    const auto start = std::chrono::high_resolution_clock::now();
    
    a.find("nonexistingbullshit");
    a.find("yonexistingbullshit");
    a.find("nonexistingbullshit");
    a.find("nonexistingbullshit");
    a.find("yonexistingbullshit");
    a.find("nonexistingbullshit_subzrtuzibil/12");
    a.find("nonexistingbullshitrtuzibil/13");
    a.find("uonexistingbullshitzrtuzibil/13");
    a.find("nonexistingbullshit_subzrtuzibil/13");

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time passed on find with " << container_name << " container: " << std::chrono::duration<double>(end - start).count() << " s.\n";
}

template <typename ContainerT>
void find3(ContainerT& a, const std::string& container_name)
{
    const auto start = std::chrono::high_resolution_clock::now();
    
    a.find("bhit");
    a.find("asdt");
    a.find("chil");
    a.find("sast");
    a.find("shi4");
    a.find("dhit");
    a.find("shat");
    a.find("ghi2");
    a.find("fhit");

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time passed on find with " << container_name << " container: " << std::chrono::duration<double>(end - start).count() << " s.\n";
}

template <typename ContainerT>
void find4(ContainerT& a, const std::string& container_name)
{
    const auto start = std::chrono::high_resolution_clock::now();
    
    a.find("bhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhitbhit");
    a.find("asdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdtasdt");
    a.find("chilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchilchil");
    a.find("sastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsastsast");
    a.find("shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4shi4");
    a.find("dhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhitdhit");
    a.find("shatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshatshat");
    a.find("ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2ghi2");
    a.find("fhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhitfhit");

    const auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time passed on find with " << container_name << " container: " << std::chrono::duration<double>(end - start).count() << " s.\n";
}

void comparison_test()
{
    local::prefix_tree<std::string, int> pt;
    std::unordered_map<std::string, int> um;
    std::map<std::string, int> mm;

    init(pt);
    init(um);
    init(mm);

    std::cout << "======= existing values ===============\n";
    find1(pt, "prefix_tree");
    find1(um, "unordered_map");
    find1(mm, "map");
    std::cout << "======= nonexisting midsized values ===\n";
    find2(pt, "prefix_tree");
    find2(um, "unordered_map");
    find2(mm, "map");
    std::cout << "======= nonexisting short values ======\n";
    find3(pt, "prefix_tree");
    find3(um, "unordered_map");
    find3(mm, "map");
    std::cout << "======= nonexisting long vales ========\n";
    find4(pt, "prefix_tree");
    find4(um, "unordered_map");
    find4(mm, "map");
}

void empty_find_test()
{
    local::prefix_tree<std::string, int> pt;
    pt.insert(std::make_pair("abcde", 5));
    auto existing_iter = pt.find("abcde");
    auto nonexisting_iter = pt.find("abc");
    if (existing_iter != pt.end()) {
        std::cout << "Find existing element test PASSED." << std::endl;
    } else {
        std::cout << "Find existing element test FAILED." << std::endl;
    }
    if (nonexisting_iter == pt.end()) {
        std::cout << "Find nonexisting element test PASSED." << std::endl;
    } else {
        std::cout << "Find nonexisting element test FAILED." << std::endl;
    }
}

void erase_test()
{
    local::prefix_tree<std::string, int> pt;
    pt.insert(std::make_pair("abcdd", 0));
    pt.insert(std::make_pair("abcee", 0));
    pt.insert(std::make_pair("abcff", 0));
    pt.insert(std::make_pair("abc", 1));
    BOOL_TEST(pt.size() == 4, "Initial size");
    pt.erase("abc");
    BOOL_TEST(pt.size() == 3, "After erase size");
    BOOL_TEST(pt.find("abc") == pt.end(), "Right element erased");
    BOOL_TEST(pt.find("abcdd") != pt.end(), "Wrong element not erased");
}

int main()
{
    //comparison_test();
    empty_find_test();
    erase_test();
}
