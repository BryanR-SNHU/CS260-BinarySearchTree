#pragma once
#include <string>
#include "BinarySearchTree.hpp"

namespace BST
{
	double strToDouble(std::string str, char ch);
	void displayBid(Bid bid);
	void loadBids(std::string csvPath, BinarySearchTree* bst);
}

