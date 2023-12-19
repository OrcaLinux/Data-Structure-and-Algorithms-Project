/*****************************************************************//**
 * @file   HuffmanTree.cpp
 * @brief   Source file implementing the HuffmanTree class responsible for managing the Huffman tree construction.
 * 
 * This file contains the declaration of the HuffmanTree class, which handles the construction of the Huffman tree
 * based on character frequencies derived from input text. The class provides functionalities to generate the tree,
 * get its encoded representation, and rebuild the tree from its encoded form.
 * 
 * To use the tree, use the suitable static function to create the tree, then use the methods of encoding or decoding
 * according to the task.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "HuffmanTree.h"

std::vector<int> HuffmanTree::calculateFrequencies(const std::string& text)
{
	// initialize a vector with 256 position all with zeros as a value.
	// each position represents a char in the ASCII code.
	std::vector<int> frequencies(256, 0);

	int length = text.length();

	// Loop for all the chars in the text, and increment its position.
	for (int i = 0; i < length; i++) {
		char c = text.at(i);
		frequencies[static_cast<unsigned char>(c)]++;
	}
	// return the freq vector.
	return frequencies;
}

bool HuffmanTree::findCharEncodingHelper(HuffmanTreeNode* node, char c, std::vector<bool>& currentEncoding,
	std::vector<bool>& encoding) {
	if (!node) {
		// If the node is null, the character is not found in this branch.
		return false;
	}
	if (node->c == c) {
		// Found the character's encoding, updating 'encoding'.
		encoding = currentEncoding;
		return true;
	}

	// Appending 'false' to the encoding path.
	currentEncoding.push_back(false);
	if (findCharEncodingHelper(node->leftChild, c, currentEncoding, encoding)) {
		// If 'c' is found in the left subtree, return true.
		return true;
	}
	// If 'c' is not in the left subtree, backtrack.
	currentEncoding.pop_back();

	// Appending 'true' to the encoding path.
	currentEncoding.push_back(true);
	if (findCharEncodingHelper(node->rightChild, c, currentEncoding, encoding)) {
		// If 'c' is found in the right subtree, return true.
		return true;
	}
	// If 'c' is not in the right subtree, backtrack.
	currentEncoding.pop_back();

	// 'c' is not found in this branch of the tree.
	return false;
}

char HuffmanTree::findCharFromEncodingHelper(HuffmanTreeNode* node, const std::vector<bool>& encoding, int index)
{
	// Return null character if node is null
	if (!node) {
		return '\0';
	}
	// Return the character when the end of encoding is reached
	if (index == encoding.size()) {
		return node->c;
	}

	// Traverse left or right based on the bit value in encoding
	if (encoding[index] == false) {
		return findCharFromEncodingHelper(node->leftChild, encoding, index + 1);
	}
	else {
		return findCharFromEncodingHelper(node->rightChild, encoding, index + 1);
	}
}

HuffmanTree* HuffmanTree::generateTreeFromText(const std::string& text)
{
	// get the frequency of each char in the text.
	std::vector<int> frequencies = calculateFrequencies(text);
	// To sort the char's freq from the least to the highest.
	// The queue will use the overridden operator() method in the HuffmanTreeNode for
	// the comparing.
	std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, HuffmanTreeNode> minHeap;

	//loop for all char frequencies, create nodes for each char that occurred in the text
	// then, add nodes to the minHeap.
	// The frequency of the node will be provided from the freq vector, and the char is
	// the position of the freq vector.
	for (int i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			minHeap.push(new HuffmanTreeNode(frequencies[i], static_cast<char>(i)));
		}
	}
	/*
	* - Loop until only the root is left alone in the minHeap
	* - The 2 nodes with the lowest freq will be combined into one node,
	*		- The smallest will be the right child of the parent node.
	*		- The other will be the left child.
	* - The parent node will be constructed with the sum of freq of the 2 nodes, and char '\0'.
	* - remove the 2 children and push the parent in the heap.
	*/
	while (minHeap.size() > 1) {
		HuffmanTreeNode* left = minHeap.top();
		minHeap.pop();
		HuffmanTreeNode* right = minHeap.top();
		minHeap.pop();

		HuffmanTreeNode* newNode = new HuffmanTreeNode(left->freq + right->freq, '\0', left, right);
		minHeap.push(newNode);
	}
	//The left node in the heap will be the root of the tree.

	return new HuffmanTree(minHeap.top());
}


HuffmanTree* HuffmanTree::rebuildTree(const std::string& encodedTree)
{
	//length of the encoded tree;
	int length = encodedTree.length();

	// Construct the frequency vector from the encoded tree.
	std::vector<int> frequencies(256, 0);

	for (int i = 0; i < length; i++) {
		char currentChar = encodedTree.at(i);
		if (currentChar == '(') {
			//get the char
			i++;
			char c = encodedTree.at(i);
			i += 2;
			//get the freq number
			std::string freq = "";
			while (encodedTree.at(i) != ')') {
				freq += encodedTree.at(i);
				i++;
			}
			//add the freq to the freq vector.
			int f = std::stoi(freq);
			frequencies[static_cast<unsigned char>(c)] = f;
		}
		else {
			throw std::runtime_error("Invalid Tree Encode");
		}
	}

	// After constructing the frequency vector, if we iterate it in the same way as in
	// generateTreeFromText(), we can get the same tree.
	
	// To sort the char's freq from the least to the highest.
	std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, HuffmanTreeNode> minHeap;

	//loop for all char frequencies, create nodes for each char that occurred in the text
	// then, add nodes to the minHeap.
	// The frequency of the node will be provided from the freq vector, and the char is
	// the position of the freq vector.
	for (int i = 0; i < 256; ++i) {
		if (frequencies[i] > 0) {
			minHeap.push(new HuffmanTreeNode(frequencies[i], static_cast<char>(i)));
		}
	}
	/*
	* - Loop until only the root is left alone in the minHeap
	* - The 2 nodes with the lowest freq will be combined into one node,
	*		- The smallest will be the right child of the parent node.
	*		- The other will be the left child.
	* - The parent node will be constructed with the sum of freq of the 2 nodes, and char '\0'.
	* - remove the 2 children and push the parent in the heap.
	*/
	while (minHeap.size() > 1) {
		HuffmanTreeNode* left = minHeap.top();
		minHeap.pop();
		HuffmanTreeNode* right = minHeap.top();
		minHeap.pop();

		HuffmanTreeNode* newNode = new HuffmanTreeNode(left->freq + right->freq, '\0', left, right);
		minHeap.push(newNode);
	}
	//The left node in the heap will be the root of the tree.

	return new HuffmanTree(minHeap.top());
}

std::string HuffmanTree::getEncodedTree()
{
	// If the tree is empty, return an empty string
	if (!root) {
		return "";
	}
	// Vector to get all the leaf nodes.
	std::vector<HuffmanTreeNode*> leafNodes;
	// Queue to hold nodes for traversal.
	std::queue<HuffmanTreeNode*> nodeQueue;
	// Add the root node to start traversal
	nodeQueue.push(root);

	// Traverse the tree to collect all leaf nodes (breadth-first search (BFS) traversal).
	while (!nodeQueue.empty()) {
		// Dequeue the front node for exploration
		HuffmanTreeNode* current = nodeQueue.front();
		nodeQueue.pop();

		if (current) {
			// Check if the current node is a leaf node
			if (!current->leftChild && !current->rightChild) {
				// Collect leaf nodes
				leafNodes.push_back(current); 
			}
			else {
				// If not a leaf node, enqueue its non-null children for further exploration
				if (current->leftChild) {
					nodeQueue.push(current->leftChild);
				}
				if (current->rightChild) {
					nodeQueue.push(current->rightChild);
				}
			}
		}
		// Continue until all nodes are explored
	}

	// Construct the encoded tree string from the leaf nodes vector
	std::string encodedTree = "(";
	for (const HuffmanTreeNode* leaf : leafNodes) {
		if (leaf->c != '\0') {
			encodedTree += '(';
			//Add char.
			encodedTree += leaf->c;
			encodedTree += ',';

			//add freq
			encodedTree += std::to_string(leaf->freq);
			encodedTree += ')';
		}
	}
	encodedTree += ")\n";
	return encodedTree;
}

std::vector<bool> HuffmanTree::getEncodingFromChar(char c)
{
	// Vector to store the character's encoding
	std::vector<bool> encoding;
	// Return an empty vector if the tree is empty
	if (!root) {
		return encoding;
	}

	// Temporary vector to store the current path
	std::vector<bool> currentEncoding;
	// Call helper function to find encoding
	findCharEncodingHelper(root, c, currentEncoding, encoding);

	return encoding;
}

char HuffmanTree::getCharFromEncoding(std::vector<bool> encoding)
{
	// Return null character if tree is empty or encoding is empty
	if (!root || encoding.empty()) {
		return '\0';
	}

	return findCharFromEncodingHelper(root, encoding, 0);
}