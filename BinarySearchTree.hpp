#pragma once
#include "Node.hpp"
#include "Bid.hpp"

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Bid bid);
	void inOrder(Node* node);
	void inOrderJSON(Node* node, std::stringstream* buffer);
	Node* removeNode(Node* node, std::string bidId);
	std::string fixQuotes(std::string source);
	int size(Node* node);
	void deleteAll(Node* node);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void InOrderJSON();
	void Insert(Bid bid);
	void Remove(std::string bidId);
	Bid Search(std::string bidId);
	int Size();
};