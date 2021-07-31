#pragma once
#include "Bid.hpp"

/**
 * Define nodes to place in the tree structure. 
 */
struct Node {
	Bid* bid;
	Node* left;
	Node* right;
};

