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
	tree_t<int> tree2 {2 , 1 , 3 , 6 , 9 , 7 };
	tree1.insert(2);
	tree1.insert(1);
	tree1.insert(3);
	tree1.insert(6);
	tree1.insert(9);
	tree1.insert(7);

	REQUIRE(tree1 == tree2);
}

TEST_CASE("remove")
{
	
	tree_t<int> tree {2 , 1 , 3 , 6 , 9 , 7 , 8};
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
// new
TEST_CASE("balance_1")
{
    tree_t<int> tree {3 ,2 , 1 };
	std::string out {
		"----3\n"
		"--2\n"
		"----1\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("balance_2")
{
    tree_t<int> tree{5 , 3 , 6 , 8 , 9 , 10 , 12 , 13};
	std::string out {
		"--------13\n"
		"------12\n"
		"----10\n"
		"------9\n"
		"--8\n"
		"------6\n"
		"----5\n"
		"------3\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("balance_3")
{
    tree_t<int> tree {1, 2 , 3 , 4 , 5 };

	std::string out {
		"------5\n"
		"----4\n"
		"------3\n"
		"--2\n"
		"----1\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("balance_4")
{
    tree_t<int> tree {10 , 85 , 15 , 70 , 20 , 60 , 30 , 50 ,65 ,80 ,90 ,40 , 5 ,55 };
	
	std::string out {
		
		"--------90\n"
		"------85\n"
		"--------80\n"
		"----70\n"
		"--------65\n"
		"------60\n"
		"----------55\n"
		"--------50\n"
		"----------40\n"
		"--30\n"
		"------20\n"
		"----15\n"
		"------10\n"
		"--------5\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_1")
{
    tree_t<int> tree {1 , 2 , 3 ,4 ,5};
	
	tree.remove(4);
	
	std::string out {
		
		"----5\n"
		"------3\n"
		"--2\n"
		"----1\n"
	};
	
	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_2")
{
    tree_t<int> tree {7,3,8,9,1,0};
	
	tree.remove(1);
	
	std::string out {
		"------9\n"
		"----8\n"
		"--7\n"
		"----3\n"
		"------0\n"
	};
	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_when_brother_is_black_and_his_right_son_is_red")
{
    tree_t<int> tree{1,2,3,4,5,6,7,8,9,10,11,0};
	
	
	tree.remove(3);
	tree.remove(2);
	
	std::string out {
		"--------11\n"
		"------10\n"
		"--------9\n"
		"----8\n"
		"------7\n"
		"--6\n"
		"------5\n"
		"----4\n"
		"------1\n"
		"--------0\n"
		
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_when_brother_is_black_and_his_sons")
{
    tree_t<int> tree{5 , 3 , 7 ,8 };
	
	tree.remove(8);
	tree.remove(3);
	
	std::string out {
		"----7\n"
		"--5\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}

TEST_CASE("delition_when_brother_is_red")
{
    tree_t<int> tree{5,3,7,8,6,2,1,9};
	
	
	tree.remove(2);
	
	std::string out {
		"--------9\n"
		"------8\n"
		"----7\n"
		"------6\n"
		"--5\n"
		"----3\n"
		"------1\n"
	};

	std::ostringstream ostream;
	tree.print(ostream , tree.root());
	
	REQUIRE(ostream.str() == out);
}
