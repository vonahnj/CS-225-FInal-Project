#include "../catch/catch.hpp"

#include "../trees/kd_tree.h"
#include "../trees/avl_tree.h"
#include "../data_reader.h"

using namespace encounters;

TEST_CASE("Test that the makefile includes KDTree", "[weight=1][valgrind]")
{
	KDTree kd;
    REQUIRE(kd.exists() == "KDTree");
}

TEST_CASE("Test that the makefile includes AVLTree", "[weight=1][valgrind]")
{
	AVLTree avl;
    REQUIRE(avl.exists() == "AVLTree");
}

TEST_CASE("Test that the makefile includes DataReader", "[weight=1][valgrind]")
{
	DataReader data;
    REQUIRE(data.exists() == "Data Reader");
}