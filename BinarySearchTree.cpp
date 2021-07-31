//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Bryan Rykowski
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "CSVparser/CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a structure to hold bid information
struct Bid {
	string bidId; // unique identifier
	string title;
	string fund;
	double amount;
	Bid() {
		amount = 0.0;
	}
};

// Define nodes to place in the tree structure.
struct Node {
	Bid* bid;
	Node* left;
	Node* right;
};

// forward declarations
double strToDouble(string str, char ch);
void displayBid(Bid bid);

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Bid bid);
	void inOrder(Node* node);
	Node* removeNode(Node* node, string bidId);
	int size(Node* node);
	void deleteAll(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Bid bid);
	void Remove(string bidId);
	Bid Search(string bidId);
	int Size();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	// initialize housekeeping variables
	root = 0;
}

void BinarySearchTree::deleteAll(Node* node) {
	if (node == 0) {
		return;
	}

	// Recurse down left and right subtrees.
	deleteAll(node->left);
	deleteAll(node->right);

	// Free memory allocated for node and the bid it points to.
	delete node->bid;
	delete node;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
	// recurse from root deleting every node
	deleteAll(this->root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	Node* node = this->root;

	if (node == 0) {
		return;
	}

	inOrder(node->left);
	displayBid(*node->bid);
	inOrder(node->right);
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
	// Check if the root is empty. If it is, insert the bid as the root.
	if (this->root == 0) {
		this->root = new Node;

		addNode(this->root, bid);
	}
	else {
		Node* cur = this->root;

		// Traverse down the tree until an empty node is found.
		while (cur != 0) {
			/* Choose to traverse down the left or right subtree depending on whether
			 * the current node's bidId is greater than or less than the bidId of the
			 * bid to insert.
			 */
			if (bid.bidId < cur->bid->bidId) {
				if (cur->left == 0) {
					cur->left = new Node;
					addNode(cur->left, bid);
					cur = 0;
				}
				else {
					cur = cur->left;
				}
			}
			else {
				if (cur->right == 0) {
					cur->right = new Node;
					addNode(cur->right, bid);
					cur = 0;
				}
				else {
					cur = cur->right;
				}
			}
		}
	}
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
	// Start at the root, setting the parent to NULL.
	Node* par = 0;
	Node* cur = this->root;

	// Search down the tree until the supplied bid or an empty node is found.
	while (cur != 0) {
		if (cur->bid->bidId == bidId) {
			// Procedure if the node to remove has no children.
			if ((cur->left == 0) && (cur->right == 0)) {
				// If the node is the root, just point it to NULL.
				if (par == 0) {
					this->root = 0;
					// Free the memory that was used by this node.
					delete cur->bid;
					delete cur;
				}
				// If the node is the left child, set the parent's left pointer to NULL.
				else if (par->left == cur) {
					// Free the memory that was used by this node.
					delete par->left->bid;
					delete par->left;
					par->left = 0;
				}
				// If the node is the right child set the parent's right pointer to NULL.
				else {
					// Free the memory that was used by this node.
					delete par->right->bid;
					delete par->right;
					par->right = 0;
				}
			}
			// Procedure if the node has a left child.
			else if ((cur->left != 0) && (cur->right == 0)) {
				// Point the root at the left child.
				if (par == 0) {
					// Free the memory that was used by this node.
					delete this->root->bid;
					delete this->root;
					this->root = cur->left;
				}
				// Set the parent's left pointer as the left child of this node.
				else if (par->left == cur) {
					par->left = cur->left;
					// Free the memory that was used by this node.
					delete cur->bid;
					delete cur;
				}
				// Set the parent's right pointer as the left child of this node.
				else {
					par->right = cur->left;
					// Free the memory that was used by this node.
					delete cur->bid;
					delete cur;
				}
			}
			// Procedure if the node has a right child.
			else if ((cur->left == 0) && (cur->right != 0)) {
				// Point the root at the right child.
				if (par == 0) {
					// Free the memory that was used by this node.
					delete this->root->bid;
					delete this->root;
					this->root = cur->right;
				}
				else if (par->left == cur) {
					par->left = cur->right;
					// Free the memory that was used by this node.
					delete cur->bid;
					delete cur;
				}
				else {
					par->right = cur->right;
					// Free the memory that was used by this node.
					delete cur->bid;
					delete cur;
				}
			}
			// Procedure if the node has two children.
			else {
				Node* suc = cur->right;

				while (suc->left != 0) {
					suc = suc->left;
				}

				// Copy the successor to the current node.
				cur->bid->bidId = suc->bid->bidId;
				cur->bid->title = suc->bid->title;
				cur->bid->fund = suc->bid->fund;
				cur->bid->amount = suc->bid->amount;

				// Recursively repeat the process.
				Remove(bidId);
			}

			return;
		}
		// Continue down the tree using the right child node.
		else if (cur->bid->bidId < bidId) {
			par = cur;
			cur = cur->right;
		}
		// Continue down the tree using the left child node.
		else {
			par = cur;
			cur = cur->left;
		}
	}
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
	// Start at the root.
	Node* cur = this->root;

	// Traverse down through the tree until the provided bid or an empty leaf is found.
	while (cur != 0) {
		// If the bidId matches return the info.
		if (cur->bid->bidId == bidId) {
			return *cur->bid;
		}
		// Otherwise compare the value of the node's bidId to provided Id and proceed down left or right.
		else if (cur->bid->bidId > bidId) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}

	// If no bid matching the bidId is found, return an empty bid.
	Bid bid;
	return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
	// Allocate memory for a bid and copy the provided info to it.
	Bid* newBid = new Bid;

	newBid->bidId = bid.bidId;
	newBid->title = bid.title;
	newBid->fund = bid.fund;
	newBid->amount = bid.amount;

	// Point the provided node at the new bid.
	node->bid = newBid;

	// Initialize the node's child pointers.
	node->left = 0;
	node->right = 0;
}
void BinarySearchTree::inOrder(Node* node) {
	// Recursively visit each node in the tree, printing the bid's info.
	if (node == 0) {
		return;
	}

	inOrder(node->left);
	displayBid(*node->bid);
	inOrder(node->right);
}
int BinarySearchTree::size(Node* node) {
	// Count the number of nodes in the tree by visiting each one and incrementing a counter.
	int count = 0;

	if (node == 0) {
		return count;
	}
	// Recurse through each subtree, returning accumulated count.
	count = count + size(node->left);
	++count;
	count = count + size(node->right);

	return count;
}
int BinarySearchTree::Size() {
	// Count the number of nodes in the tree by visiting each one and incrementing a counter.
	Node* node = this->root;

	int count = 0;

	if (node == 0) {
		return count;
	}
	// Recurse through each subtree, returning accumulated count.
	count = count + size(node->left);
	++count;
	count = count + size(node->right);

	return count;
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
	cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << endl;
	return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	// read and display header row - optional
	/*
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;
	*/

	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			//cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bst->Insert(bid);
		}
	}
	catch (csv::Error& e) {
		std::cerr << e.what() << std::endl;
	}
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

	// process command line arguments
	string csvPath = "";
	string bidKey = "";

	switch (argc) {
	case 2:
		csvPath = argv[1];
		bidKey = "98109";
		break;
	case 3:
		csvPath = argv[1];
		bidKey = argv[2];
		break;
	default:
		csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
		bidKey = "98109";
	}

	// Define a timer variable
	clock_t ticks;

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;
	bst = new BinarySearchTree();

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  4. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			loadBids(csvPath, bst);

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			cout << bst->Size() << " bids read" << endl;

			// Calculate elapsed time and display result
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
			break;

		case 2:
			bst->InOrder();
			break;

		case 3:
			ticks = clock();

			bid = bst->Search(bidKey);

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) {
				displayBid(bid);
			}
			else {
				cout << "Bid Id " << bidKey << " not found." << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

			break;

		case 4:
			bst->Remove(bidKey);
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}
