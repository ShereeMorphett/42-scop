#include "tests.hpp"
#include "ft.hpp"
#include <algorithm> 

TEST_CASE("test functions")
{
    CHECK(std::max(1, 2) == 2);
    CHECK(std::max(2, 2) == 2);
    CHECK(std::max(-1, 2) == 2);
    CHECK(std::max(-1, -2) == -1);
    CHECK(std::max(0, 5) == 5);   
}

TEST_CASE("test functions from ft")
{
    CHECK(ft::add(1, 2) == 3);
 
}