#include <map>
#include <string>

#include <prefix_tree.h>

#include "unit_test_helper.h"

void test_constructors()
{
BEGIN_TEST_GROUP("Constructors")

    local::prefix_tree<std::string, int> pt{
        { "zero", 0 },
        { "one", 1 },
        { "two", 2 },
        { "three", 3 }
    };
    TEST(pt.size() == 4
                && pt["zero"] == 0
                && pt["one"] == 1
                && pt["two"] == 2
                && pt["three"] == 3, "CTOR1");

    std::map<std::string, int> m{
        { "zero", 0 },
        { "one", 1 },
        { "two", 2 },
        { "three", 3 }
    };
    local::prefix_tree<std::string, int> pt2(m.begin(), m.end());
    TEST(pt2.size() == 4
                && pt2["zero"] == 0
                && pt2["one"] == 1
                && pt2["two"] == 2
                && pt2["three"] == 3, "CTOR2");

    local::prefix_tree<std::string, int> pt3(pt);
    TEST(pt3.size() == 4
                && pt3["zero"] == 0
                && pt3["one"] == 1
                && pt3["two"] == 2
                && pt3["three"] == 3, "CTOR3");

    local::prefix_tree<std::string, int> pt4(std::move(pt3));
    TEST(pt4.size() == 4
                && pt4["zero"] == 0
                && pt4["one"] == 1
                && pt4["two"] == 2
                && pt4["three"] == 3
                && pt3.empty(), "CTOR4");

    local::prefix_tree<std::string, int> pt5;
    pt5 = pt4;
    TEST(pt5.size() == 4
                && pt5["zero"] == 0
                && pt5["one"] == 1
                && pt5["two"] == 2
                && pt5["three"] == 3, "CTOR5");

    pt5 = std::move(pt4);
    TEST(pt5.size() == 4
                && pt5["zero"] == 0
                && pt5["one"] == 1
                && pt5["two"] == 2
                && pt5["three"] == 3
                && pt4.empty(), "CTOR6");

END_TEST_GROUP()
}

void test_selectors()
{
BEGIN_TEST_GROUP("Selectors")

    local::prefix_tree<std::string, int> pt;
    TEST(pt.empty() && pt.size() == 0, "SEL1");

    local::prefix_tree<std::string, int> pt2{
        { "zero", 0 },
        { "one", 1 },
        { "two", 2 },
        { "three", 3 }
    };
    TEST(!pt2.empty() && pt2.size() == 4, "SEL2");

    auto iter = pt2.find("two");
    TEST(iter != pt2.end()
                && iter->first == "two"
                && iter->second == 2, "SEL3");

    iter = pt2.find("nine");
    TEST(iter == pt2.end(), "SEL4");
    
    TEST((pt.max_size() == std::numeric_limits<local::prefix_tree<std::string, int>::size_type>::max()), "SEL5");

END_TEST_GROUP()
}

void test_mutators()
{
BEGIN_TEST_GROUP("Mutators")

    local::prefix_tree<std::string, int> pt;
    pt.insert("one", 1);
    TEST(pt.size() == 1 && pt["one"] == 1, "MUT1");

    pt["one"] = 3;
    TEST(pt.size() == 1 && pt["one"] == 3, "MUT2");

    pt["two"] = 2;
    TEST(pt.size() == 2 && pt["two"] == 2, "MUT3");

    pt.insert(std::make_pair("nine", 9));
    TEST(pt.size() == 3 && pt["nine"] == 9, "MUT4");

    pt.clear();
    TEST(pt.empty(), "MUT5");

    pt.insert("aaa", 1);
    pt.insert("aaabc", 2);
    TEST(pt.size() == 2, "MUT6");

    pt.erase("aaabc");
    TEST(pt.size() == 1
                && pt.find("aaab") == pt.end()
                && pt.find("aaa") != pt.end(), "MUT7");

    pt.clear();
    pt.insert("aaab", 1);
    pt.insert("aaac", 2);
    pt.insert("aaad", 3);
    pt.insert("aaae", 4);
    TEST(pt.size() == 4
                && pt["aaab"] == 1
                && pt["aaac"] == 2
                && pt["aaad"] == 3
                && pt["aaae"] == 4, "MUT8");

    auto iter = pt.find("aaac");
    iter = pt.erase(iter);
    TEST(iter != pt.end() && iter->second == 3, "MUT9");

    iter = pt.erase(pt.find("aaae"));
    TEST(iter == pt.end(), "MUT10");

END_TEST_GROUP()
}

void test_iterators()
{
BEGIN_TEST_GROUP("Iterators")

    local::prefix_tree<std::string, int> pt;
    TEST(pt.begin() == pt.end(), "ITER1");

    std::map<std::string, int> m;
    for (int i = 0; i < 100; ++i) {
        std::string key;
        key.push_back(i % 5);
        key.push_back(i % 10);
        key.push_back(i);
        pt.insert({ key, i });
        m.insert({ key, i });
    }
    TEST(std::equal(pt.begin(), pt.end(), m.begin()), "ITER2");

    auto it = pt.begin();
    std::advance(it, pt.size());
    TEST(it == pt.end(), "ITER3");

END_TEST_GROUP()
}

void test_operators()
{
BEGIN_TEST_GROUP("Operators")

    local::prefix_tree<std::string, int> pt1, pt2;
    TEST(pt1 == pt2, "OP1");

    std::map<std::string, int> m1, m2;
    for (int i = 0; i < 100; ++i) {
        std::string key1, key2;
        key1.push_back(i % 5);
        key1.push_back(i % 10);
        key1.push_back(i);
        pt1.insert({ key1, i });
        m1.insert({ key1, i });

        key2.push_back(i % 10);
        key2.push_back(i % 5);
        key2.push_back(i);
        pt2.insert({ key2, i });
        m2.insert({ key2, i });
    }

    local::prefix_tree<std::string, int> tmp(m1.begin(), m1.end());
    TEST(tmp == pt1, "OP2");

    TEST((pt1 == pt2) == (m1 == m2), "OP3");
    TEST((pt1 != pt2) == (m1 != m2), "OP4");
    TEST((pt1 <= pt2) == (m1 <= m2), "OP5");
    TEST((pt1 >= pt2) == (m1 >= m2), "OP6");
    TEST((pt1 < pt2) == (m1 < m2), "OP7");
    TEST((pt1 > pt2) == (m1 > m2), "OP8");

END_TEST_GROUP()
}

int main()
{
    test_constructors();
    test_selectors();
    test_mutators();
    test_iterators();
    test_operators();
}
