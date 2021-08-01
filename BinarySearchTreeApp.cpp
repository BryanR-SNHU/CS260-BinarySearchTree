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
#include "Node.hpp"
#include "Bid.hpp"
#include "StaticMethods.hpp"

using namespace std;

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
		csvPath = "example.csv";
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
			BST::loadBids(csvPath, bst);

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
				BST::displayBid(bid);
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
