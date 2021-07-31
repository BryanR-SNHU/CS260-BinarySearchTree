#pragma once
#include <string>

/**
 * Define a structure to hold bid information.
 */
struct Bid {
	std::string bidId; // unique identifier
	std::string title;
	std::string fund;
	double amount;
	Bid();
};

