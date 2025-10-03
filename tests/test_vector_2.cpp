// test_vector_iterator.cpp
//#define CATCH_CONFIG_MAIN // must be in one
#include "catch2/catch.hpp"
#include <algorithm>  //for std::max
#include "vector.hpp"
#include "matrix.hpp"

/* iterator test cases */
TEST_CASE("iterator non-const iterator dereference", "[iterator]") {
    dsa::Vector<int> v; bool ok{true};
    for (int i{1}; i<=5; i++) 
        v.push_back(i);
    auto it = v.begin();
    ok = ok && (*it == 1);
    *it = 10;
    ok = ok && (v[0] == 10);
    
    REQUIRE(ok);
}

TEST_CASE("non-const empty vector begin==end", "[iterator]") {
    dsa::Vector<int> v;  // empty vector

    auto it_begin = v.begin();
    auto it_end = v.end();

    REQUIRE(it_begin == it_end);  // should be true for empty vector
}

TEST_CASE("iterator begin() and end()", "[iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i)
        v.push_back(i);

    int expected = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        REQUIRE(*it == expected);
        ++expected;
    }
}

TEST_CASE("iterator pre/post-increment operator", "[iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i)
        v.push_back(i);

    auto it = v.begin();
    ++it;
    REQUIRE(*it == 1);

    auto it2 = it++;
    REQUIRE(*it2 == 1);  // old value
    REQUIRE(*it == 2);   // incremented

}

TEST_CASE("iterator pre/post-decrement operator", "[iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i)
        v.push_back(i);

    auto it = v.end();
    --it;
    REQUIRE(*it == 4);   // last element

    auto it2 = it--;
    REQUIRE(*it2 == 4);  // old value
    REQUIRE(*it == 3);   // decremented value
}

/* const iterator test cases */ 
TEST_CASE("const_iterator dereference", "[const iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;
    bool ok = true;

    auto it = cv.begin();
    ok = ok && (*it == 0);

    ++it;
    ok = ok && (*it == 1);

    REQUIRE(ok);
}

TEST_CASE("const_iterator begin() and end()", "[const iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;

    int expected = 0;
    for (auto it = cv.begin(); it != cv.end(); ++it) {
        REQUIRE(*it == expected);
        ++expected;
    }
}

TEST_CASE("const_iterator pre/post-increment operator", "[const iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;
    auto it = cv.begin();
    ++it;
    REQUIRE(*it == 1);

    auto it2 = it++;
    REQUIRE(*it2 == 1);  // old value
    REQUIRE(*it == 2);   // incremented
}

TEST_CASE("const_iterator pre/post-decrement operator", "[const iterator]") {
    dsa::Vector<int> v;
    for (int i{0}; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;
    auto it = cv.end();
    --it;
    REQUIRE(*it == 4);   // last element

    auto it2 = it--;
    REQUIRE(*it2 == 4);  // old value
    REQUIRE(*it == 3);   // decremented value
}


TEST_CASE("const_iterator cannot mutate elements", "[const_iterator]") {
    dsa::Vector<int> v;
    for (int i = 0; i < 5; ++i) 
        v.push_back(i);
    const dsa::Vector<int>& cv = v;

    auto cit = cv.begin();

    REQUIRE(*cit == 0);
    // Confirm original value is unchanged
    REQUIRE(cv.at(0) == 0);
}

/* matrix test cases */
TEST_CASE("Constructor", "[matrix]") {
    dsa::Matrix A(2, 3);

    REQUIRE(A.getRows() == 2); 
    REQUIRE(A.getCols() == 3); 

    // Check that all elements are 0
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            REQUIRE(A(i,j) == 0);
        }
    }

    // Check negative dimensions throw
    REQUIRE_THROWS_AS(dsa::Matrix(-1, 3), std::out_of_range);
    REQUIRE_THROWS_AS(dsa::Matrix(2, -5), std::out_of_range);
}

TEST_CASE("operator", "[matrix]") {
    dsa::Matrix A(2, 2);

    A(0,0) = 5;
    A(1,1) = 10;

    REQUIRE(A(0,0) == 5);
    REQUIRE(A(0,1) == 0);  // defaults to 0
    REQUIRE(A(1,0) == 0);
    REQUIRE(A(1,1) == 10);

    REQUIRE_THROWS_AS(A(2,0), std::out_of_range);
    REQUIRE_THROWS_AS(A(0,2), std::out_of_range);
}

TEST_CASE("Matrix Addition, different size", "[matrix]") {
    dsa::Matrix A(1, 2); // declare matrix with default 0
    // assign values as below or in loop
    A(0,0)=1; A(0,1)=2;
    dsa::Matrix B(2, 2); //different row
    dsa::Matrix C(1, 3); //different col
    dsa::Matrix D(3, 3); //different row and col

    REQUIRE_THROWS_AS(A + B, std::out_of_range);
    REQUIRE_THROWS_AS(A + C, std::out_of_range);
    REQUIRE_THROWS_AS(A + D, std::out_of_range);
}

TEST_CASE("Matrix Addition, same size", "[matrix]") {
    dsa::Matrix A(1, 2), B(1, 2); // declare matrix with default 0
    // assign values as below or in loop
    A(0,0)=1; A(0,1)=2;
    B(0,0)=3; B(0,1)=4;

    dsa::Matrix A_plus_B_expected(1, 2);
    A_plus_B_expected(0,0)=4; A_plus_B_expected(0,1)=6;
    
    dsa::Matrix A_plus_B_actual = A + B;

    // Check equality element-wise
    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 2; j++) {
            REQUIRE(A_plus_B_actual(i,j) == A_plus_B_expected(i, j));
        }
    }
}