/*****************************************************************//**
 * @file   HuffmanTreeNode.h
 * @brief  A Tree Node created for the Huffman Encoding Tree.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef HUFFMAN_TREE_NODE_H
#define  HUFFMAN_TREE_NODE_H

class HuffmanTreeNode
{
	friend class HuffmanTree;
public:
	//freq of the node.
	int freq;
	//
	// Holds the character associated with the node.
	// Have a value only for the leaf Node, other wise the char will be '\0'.
	//
	char c;
	//children of the node, nullptr if it was a leaf.

	HuffmanTreeNode* leftChild;
	HuffmanTreeNode* rightChild;

public:
	//C'tor s
	/**
	 * @brief An empty C'tor.
	 * Initialize the c with '\o', freq with 0, both children with nullptr.
	 *
	 */
    explicit HuffmanTreeNode()
		: freq(0), c('\0'), leftChild(nullptr), rightChild(nullptr) {}

	/**
	 * @brief Constructs a HuffmanTreeNode with specified frequency, character, left, and right children.
	 * @param frequency The frequency associated with the node.
	 * @param character The character associated with the node.
	 * @param left A pointer to the left child node.
	 * @param right A pointer to the right child node.
	 */
    HuffmanTreeNode(int frequency, char character, HuffmanTreeNode* left, HuffmanTreeNode* right)
		: freq(frequency), c(character), leftChild(left), rightChild(right) {}

	/**
	 * @brief Constructs a leaf HuffmanTreeNode with specified frequency and character.
	 * @param frequency The frequency associated with the leaf node.
	 * @param character The character associated with the leaf node.
	 */
    HuffmanTreeNode(int frequency, char character)
		: freq(frequency), c(character), leftChild(nullptr), rightChild(nullptr) {}

	/**
	 * @brief D'tor that deallocates the children.
	 *
	 */
    ~HuffmanTreeNode() {
		// Deallocate left and right child nodes if they exist
		if (leftChild != nullptr) {
			delete leftChild;
			leftChild = nullptr;
		}
		if (rightChild != nullptr) {
			delete rightChild;
			rightChild = nullptr;
		}
	}

	/**
	 * @brief Overloads the less-than operator (<) to compare HuffmanTreeNode objects based on their frequencies.
	 * But we need the smallest nodes at the start of the priority_queue, so do the opposite in the implementation.
	 *
	 * @param other The HuffmanTreeNode object to compare with.
	 * @return True if the frequency of this node is more than the frequency of the other node, false otherwise.
	 */
    bool operator<(const HuffmanTreeNode& other) const { return freq > other.freq; }

	/**
	* @brief Overloaded () operator for comparing HuffmanTreeNode pointers.
	*
	* This operator compares two HuffmanTreeNode pointers based on
	* the comparison of the nodes themselves.
	*
	* @param x Pointer to the first HuffmanTreeNode to compare.
	* @param y Pointer to the second HuffmanTreeNode to compare.
	* @return True if the first node has higher priority than the second node.
	*/
	bool operator () (const HuffmanTreeNode* x, const HuffmanTreeNode* y) {
		return *x < *y;
	}
};

#endif // !HUFFMAN_TREE_NODE_H
