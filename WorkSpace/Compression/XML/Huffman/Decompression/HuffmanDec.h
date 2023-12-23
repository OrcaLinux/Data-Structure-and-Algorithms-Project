/*****************************************************************//**
 * @file   HuffmanDec.h
 * @brief   Header file for Huffman Decompression algorithm.
 * 
 * This file defines the HuffmanDec class, which implements Huffman decompression.
 * It provides functionality to decompress data using a Huffman tree's encoded representation.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef HUFFMAN_DEC_H
#define HUFFMAN_DEC_H
#include "HuffmanTree.h"

class HuffmanDec
{
private:
	// tree holds the encoding.
	HuffmanTree* tree;
	// the file to decompress.
	std::string* file;
	// number of bits in the compressed file
	long long bitsLength;

public:
	/**
	 * @brief C'tor.
	 *
	 * It will construct the tree from the HuffmanTree::rebuildTree() 
	 * static method, and the encoded tree line (the first line in the compressed file.)
	 *
	 * @param fileC file to decompress
	 */
	explicit HuffmanDec(std::string* file);

	/**
	 * @brief D'tor.
	 * 
	 */
	~HuffmanDec() {
		delete tree;
		if (file != nullptr) {
			delete file;
		}
	}

	/**
   * @brief Decompresses the file content using the Huffman tree.
   *
   * This function decompresses the file content using the Huffman tree's encoded representation.
   * It decodes the bits based on the Huffman tree and returns the decompressed string.
   *
   * @return A pointer to the decompressed string.
   */
	std::string* decompress();
};

#endif // !HUFFMAN_DEC_H
