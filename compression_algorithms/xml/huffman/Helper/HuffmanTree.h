/*****************************************************************//**
 * @file   HuffmanTree.h
 * @brief  Header file defining the HuffmanTree class responsible for managing the Huffman tree construction.
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
#pragma once
#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H
#include "HuffmanTreeNode.h"
#include <vector>
#include <queue>
#include <algorithm>

class HuffmanTree
{
private:
	HuffmanTreeNode* root;

	// Helper methods.
	/**
	 * @brief Calculates the frequency of each character in the passed string.
	 * 
	 * It uses the concept of frequency array, the array is 256 in size, each position
	 * for an element according to its ASCII code).
	 * 
	 * @note It will work only with ASCII characters, you can't use any other characters.
	 * 
	 * @param text
	 * @return frequency vector of size 256.
	 */
	static std::vector<int> calculateFrequencies(const std::string& text);

	/**
	 * @brief Recursively searches for the encoding of a character in a Huffman tree.
	 *
	 * This function searches for the encoding (binary representation) of a character 'c'
	 * within the Huffman tree starting from a given node. It traverses the tree recursively
	 * using a depth-first search and updates the 'encoding' vector with the binary encoding
	 * found for the character.
	 *
	 * For the left subtree path, a 0 is added to the encoding.
	 * 
	 * @param node Pointer to the current node in the Huffman tree.
	 * @param c The character to find the encoding for.
	 * @param currentEncoding Vector storing the current binary encoding path.
	 * @param encoding Vector storing the final binary encoding of the character 'c'.
	 * @return True if the encoding for the character 'c' is found, false otherwise.
	 */
	bool findCharEncodingHelper(HuffmanTreeNode* node, char c,
		std::vector<bool>& currentEncoding, std::vector<bool>& encoding);

	/**
	 * @brief Recursively finds a character from its binary encoding in a Huffman tree.
	 *
	 * This function traverses the Huffman tree based on the provided binary encoding
	 * to find the corresponding character. It starts from the given 'node' and follows
	 * the encoding path (using 'index') to locate the character encoded in the tree.
	 *
	 * @param node Pointer to the current node in the Huffman tree.
	 * @param encoding Vector containing the binary encoding of a character.
	 * @param index Index used to traverse the binary encoding vector.
	 * @return The character decoded from the given binary encoding.
	 */
	char findCharFromEncodingHelper(HuffmanTreeNode* node, const std::vector<bool>& encoding, int index);

public:

	/**
	 * @brief An empty C'tor.
	 * Initialize the root with nullptr.
	 *
	 */
	explicit HuffmanTree(HuffmanTreeNode* root) : root(root) {}
	/**
	 *  @brief D'tor that deallocates the root.
	 *	the root will delete all its children.
	 */
	~HuffmanTree() { delete root; }

	//Static methods for building the tree
	/**
	 * @brief Generates a Huffman tree from the provided text.
	 *
	 * @param text The input text used to construct the tree.
	 * @return A pointer to the generated HuffmanTree object.
	 */
	static HuffmanTree* generateTreeFromText(const std::string& text);

	/**
	 * @brief Rebuilds a Huffman tree from its encoded representation (The first line in the
	 * compressed text that ends with ")\n").
	 *
	 * If will be in this formate:
	 *- Parentheses-based representation: "((A:01)(B:10))\n", where each node and its encoding are
	 * enclosed in parentheses.
	 *
	 * @param encodedTree The encoded representation of the tree, without the 1st "(" and ")\n".
	 * @return A pointer to the reconstructed HuffmanTree object.
	 */
	static HuffmanTree* rebuildTree(const std::string& encodedTree);

	//methods
	//for encoding
	/**
	 * @brief Retrieves the encoding for a specific character from the tree.
	 *
	 * The string will be in this formate:
	 * - Parentheses-based representation: "((A:01)(B:10)\n", where each node and its encoding are
	 * enclosed in parentheses.
	 *
	 * @return The encoding tree string to add to the compressed file.
	 */
	std::string getEncodedTree();

	/**
	 * @brief Get the Huffman encoding for a specific character in the tree.
	 *
	 * This function retrieves the Huffman encoding (binary representation)
	 * for a specific character 'c' within the Huffman tree. It uses a helper
	 * function findCharEncodingHelper to traverse the tree and find the encoding.
	 *
	 * @param c The character to find the encoding for.
	 * @return A vector of boolean values representing the binary encoding of the character.
	 */
	std::vector<bool> getEncodingFromChar(char c);

	//for decoding
	/**
	 * @brief Get the character represented by a specific Huffman encoding in the tree.
	 *
	 * This function retrieves the character represented by a given Huffman encoding
	 * (binary representation) within the Huffman tree. It uses a helper function
	 * findCharFromEncodingHelper to traverse the tree and find the character.
	 *
	 * Pass the bits in its order from left to right in the vector, i.e., MSB (left most bit) 
	 * at position zero.
	 * 
	 * @param encoding A vector of boolean values representing the binary encoding to decode.
	 * @return The character represented by the given encoding.
	 */
	char getCharFromEncoding(std::vector<bool> encoding);
};
#endif // !HUFFMAN_TREE_H
