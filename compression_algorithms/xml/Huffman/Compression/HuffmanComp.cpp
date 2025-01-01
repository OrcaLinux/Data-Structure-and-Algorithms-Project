/*****************************************************************//**
 * @file   HuffmanComp.cpp
 * @brief   Source file for Huffman Compression algorithm.
 * 
 * This file implements the HuffmanComp class, which implements Huffman compression.
 * It utilizes HuffmanTree for encoding and generates compressed output
 * based on the Huffman tree's encoded representation.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "HuffmanComp.h"

std::string* HuffmanComp::compress()
{
	// add the encoding table in the 1st line of the compressed file.
	std::string* compressedString = new std::string(tree->getEncodedTree());

	// Encode each character in the file content using the Huffman tree
	std::string bits = "";
	for (char c : *file) {
		std::vector<bool> encoding = tree->getEncodingFromChar(c);
		for (bool bit : encoding) {
			bits += (bit ? '1' : '0');
		}
	}

	// Add the total number of bits so it can be retrieved at decompression.
	*compressedString += std::to_string(bits.size()) + "\n";

	//add the bits
	*compressedString += bits;

	return compressedString;
}
