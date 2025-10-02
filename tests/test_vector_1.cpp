// test_vector.cpp
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "vector.hpp"
#include <stdexcept>

// test cases from Part 1
// create const vector for testing
TEST_CASE("Default constructor creates empty vector", "[constructor]") {
    dsa::Vector<int> v;
    bool ok{true};
    REQUIRE(ok);
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 0);
}

TEST_CASE("Reserve increases capacity", "[reserve]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    
    int old_cap = v.capacity();

    v.reserve(old_cap + 2);
    REQUIRE(v.capacity() == old_cap + 2);

    v.reserve(old_cap + 10);
    REQUIRE(v.capacity() == old_cap + 10);

    v.reserve(old_cap + 100);
    REQUIRE(v.capacity() == old_cap + 100);
    REQUIRE(v.size() == 5); // size unchanged

}

TEST_CASE("Reserve with small", "[reserve]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    int old_cap = v.capacity();
    v.reserve(1);
    REQUIRE(v.capacity() == old_cap);
}

TEST_CASE("push_back grows size and stores", "[push_back]") {
    dsa::Vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
        REQUIRE(v.size() == i + 1);
        REQUIRE(v[i] == i);
    }
}

TEST_CASE("pop_back reduces size", "[pop_back]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    int old_cap = v.capacity();
    v.pop_back();
    REQUIRE(v.size() == 4);
    REQUIRE(v.capacity() <= old_cap); // shrink may happen
}

TEST_CASE("pop_back on empty vector", "[pop_back][edge]") {
    dsa::Vector<int> v;
    REQUIRE(v.size() == 0);
    v.pop_back(); // should not throw
    REQUIRE(v.size() == -1);
}

TEST_CASE("insert in middle and end", "[insert]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    v.insert(2, 42);
    REQUIRE(v[2] == 42);
    REQUIRE(v.size() == 6);

    v.insert(v.size(), 99); // insert at end
    REQUIRE(v.back() == 99);
    REQUIRE(v.size() == 7);
}

TEST_CASE("erase", "[erase]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    v.erase(2);
    REQUIRE(v.size() == 4);
    REQUIRE(v[2] == 3);

    v.erase(0);
    REQUIRE(v.front() == 1);
    REQUIRE(v.size() == 3);
}

TEST_CASE("capacity accessor", "[capacity]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;

    REQUIRE(v.capacity() >= v.size());
    REQUIRE(cv.capacity() >= cv.size());
}

TEST_CASE("size accessor", "[size]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;    

    REQUIRE(v.size() == 5);
    REQUIRE(cv.size() == 5);
}

TEST_CASE("empty", "[empty][edge]") {
    dsa::Vector<int> v;
    REQUIRE(v.empty());
    v.push_back(1);
    REQUIRE(!v.empty());
    v.pop_back();
    REQUIRE(v.empty());   
}

TEST_CASE("operator[] (non-const)", "[operator][non-const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    v[2] = 42;
    REQUIRE(v[2] == 42);
}

TEST_CASE("operator[] (const)", "[operator][const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;    
    REQUIRE(cv[3] == 3);
}

TEST_CASE("at (non-const)", "[at][non-const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    v.at(1) = 99;
    REQUIRE(v.at(1) == 99);
}

TEST_CASE("at (const)", "[at][const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;   
    REQUIRE(cv.at(4) == 4); 
}

TEST_CASE("at throws out of range (non-const)", "[at][non-const][exception][edge]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
    REQUIRE_THROWS_AS(v.at(-1), std::out_of_range);
}

TEST_CASE("at throws out of range (const)", "[at][const][exception][edge]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;   
    REQUIRE_THROWS_AS(cv.at(5), std::out_of_range);
    REQUIRE_THROWS_AS(cv.at(-1), std::out_of_range); 
}

TEST_CASE("front (non-const)", "[front][non-const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    REQUIRE(v.front() == 0);
    v.front() = 42;
    REQUIRE(v.front() == 42);
}

TEST_CASE("front (const)", "[front][const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;
    REQUIRE(cv.front() == 0);    
}

TEST_CASE("back (non-const)", "[back][non-const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    REQUIRE(v.back() == 4);
    v.back() = 99;
    REQUIRE(v.back() == 99);
}

TEST_CASE("back (const)", "[back][const]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;   
    REQUIRE(cv.back() == 4); 
}

TEST_CASE("shrink when size <= cap/4, shrink keeps at least one slot", "[shrink]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    int old_cap = v.capacity();

    // Remove elements so size <= cap/4
    for (int i = 0; i < 4; ++i)
        v.pop_back();

    REQUIRE(v.size() == 1);
    REQUIRE(v.capacity() < old_cap);   // capacity should shrink
    REQUIRE(v.capacity() >= 1);        // but never below 1
}

TEST_CASE("shrink when size > cap/4", "[shrink]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    int old_cap = v.capacity();
    v.shrink();
    REQUIRE(v.capacity() == old_cap); // should not shrink
}

TEST_CASE("shrink via pop-back", "[shrink][pop-back]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    int old_cap = v.capacity(); //cap = 8
    for (int i = 0; i < 3; ++i) 
        v.pop_back();  // shrink triggered internally, until size <= cap/4 = 2

    REQUIRE(v.size() == 2);
    REQUIRE(v.capacity() < old_cap);  // capacity reduced
}

TEST_CASE("shrink never goes below 1", "[shrink]") {
    dsa::Vector<int> v;
    v.push_back(42);

    v.pop_back(); // now empty
    REQUIRE(v.size() == 0);
    REQUIRE(v.capacity() >= 1);
}

TEST_CASE("shrink_to_fit with max(1, sz)", "[shrink]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);

    v.reserve(50);
    REQUIRE(v.capacity() >= 50);

    v.shrink_to_fit();
    REQUIRE(v.capacity() == v.size());
}

TEST_CASE("shrink_to_fit when size==cap", "[shrink][edge]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 4; ++i) 
        v.push_back(i);
    int old_cap = v.capacity();
    v.shrink_to_fit();
    REQUIRE(v.capacity() == old_cap); // 4 elements
}