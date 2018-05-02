#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating_tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("insert_and_print") 
{
	tree_t<int> tree;
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(6);
	tree.insert(9);
	tree.insert(7);
	tree.insert(8);
	
	std::string out {
		"--------9\n"
		"------8\n"
		"--------7\n"
		"----6\n"
		"------3\n"
		"--2\n"
		"----1\n"
	};
	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	REQUIRE(ostream.str() == out);
}

TEST_CASE("find")
{
	tree_t<int> tree;
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(6);
	tree.insert(9);
	tree.insert(7);
	tree.insert(8);
	
	REQUIRE(tree.find(5) == false);
	REQUIRE(tree.find(8) == true);
	REQUIRE(tree.find(9) == true);	
	REQUIRE(tree.find(7) == true);
}

TEST_CASE("equal")
{
	tree_t<int> tree1;
	tree_t<int> tree2;
	//tree_t<int> tree2 {2 , 1 , 3 , 6 , 9 , 7 };
	tree1.insert(2);
	tree1.insert(1);
	tree1.insert(3);
	tree1.insert(6);
	tree1.insert(9);
	tree1.insert(7);
	
	tree2.insert(2);
	tree2.insert(1);
	tree2.insert(3);
	tree2.insert(6);
	tree2.insert(9);
	tree2.insert(7);
	
	REQUIRE(tree1 == tree2);
}

TEST_CASE("remove")
{
	
	//tree_t<int> tree {2 , 1 , 3 , 6 , 9 , 7 , 8};
	tree_t<int> tree;
	tree.insert(2);
	tree.insert(1);
	tree.insert(3);
	tree.insert(6);
	tree.insert(9);
	tree.insert(7);
	tree.insert(8);
	std::string out {
		"------9\n"
		"----8\n"
		"------7\n"
		"--6\n"
		"------3\n"
		"----2\n"
	};
	bool one = tree.remove(1);
	bool two = tree.remove(10);
	
	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
	REQUIRE(one);
	REQUIRE(!two);
}
