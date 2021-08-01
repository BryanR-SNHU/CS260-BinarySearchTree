#include "BinarySearchTree.hpp"
#include "StaticMethods.hpp"

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
	BST::displayBid(*node->bid);
	inOrder(node->right);
}
/**
 * Insert a bid
 * @param bid: The bid to insert.
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
 * @param bidId: The id of the bid to remove.
 */
void BinarySearchTree::Remove(std::string bidId) {
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
 * @param bidId: Id to search for.
 * @return If the bid exists, it is returned. Otherwise, an empty bid is returned.
 */
Bid BinarySearchTree::Search(std::string bidId) {
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

/**
* Print out info about every bid in the tree, in order.
* @param node: The node to visit.
*/
void BinarySearchTree::inOrder(Node* node) {
	// Recursively visit each node in the tree, printing the bid's info.
	if (node == 0) {
		return;
	}

	inOrder(node->left);
	BST::displayBid(*node->bid);
	inOrder(node->right);
}

/**
* Get size of tree in nodes.
* @param node: The node to visit.
* @return The number of nodes as an integer.
*/
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

/**
* Get size of tree in nodes.
* @param node: The node to visit.
* @return The number of nodes as an integer.
*/
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