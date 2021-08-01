#include "StaticMethods.hpp"
#include <iostream>
#include "CSVparser/CSVparser.hpp"

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch: The character to strip out
 * @return The number in the string in the form of a double.
 */
double BST::strToDouble(std::string str, char ch)
{
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid: struct containing the bid info.
 */
void BST::displayBid(Bid bid)
{
	std::cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
		<< bid.fund << std::endl;
	return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath: The path to the CSV file to load
 * @return A container holding all the bids read
 */
void BST::loadBids(std::string csvPath, BinarySearchTree* bst) 
{
	std::cout << "Loading CSV file " << csvPath << std::endl;

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