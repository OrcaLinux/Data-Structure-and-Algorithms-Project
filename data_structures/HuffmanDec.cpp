/*****************************************************************//**
 * @file   HuffmanDec.cpp
 * @brief  Source file for Huffman Decompression algorithm.
 * 
 * This file implements the HuffmanDec class, which implements Huffman decompression.
 * It provides functionality to decompress data using a Huffman tree's encoded representation.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#include "HuffmanDec.h"

HuffmanDec::HuffmanDec(std::string* file) : file(file) {
	if (!file->empty()) {
		// Find the end of the encoded tree.
		int endPos = file->find(")\n"); 

		//get the number of bits.
		int endNumPos = file->find("\n", endPos);
		std::string bitsNum = file->substr(endPos + 2, endNumPos - endPos - 3);
		this->bitsLength = std::stoi(bitsNum);

		//build the tree.
		if (endPos != std::string::npos) {
			// Exclude the ")\n" at the end and the first "("
			std::string encodedTree = file->substr(1, endPos - 1);
			tree = HuffmanTree::rebuildTree(encodedTree);
		}
	}
	else {
		throw std::runtime_error("Defected file.");
	}
}

std::string* HuffmanDec::decompress() {
	if (!tree || !file || file->empty()) {
		// Cannot decompress without a tree or compressed data
		return nullptr; 
	}

	// Find the end of the encoded tree
	int startPos = file->find(")\n") + 2; 
	// Find the end of the bits number.
	startPos = file->find("\n", startPos) + 1;

	//get the bits after the number of bits line, loop only for the requited bits
	//(total as the number of bits in the second line.) and skip the extra added bits in the last.
	if (startPos != std::string::npos && startPos < file->size()) {
		// Extract compressed bits
		std::string compressedBits = file->substr(startPos); 

		std::string* decompressedString = new std::string();
		std::vector<bool> encoding;

		// Loop through the bits and reconstruct the original string
		for (int i = 0; i < this->bitsLength; i++) {
			//get the current bit.
			char bit = compressedBits.at(i);
			//push to the encoding vector as a boolean value.
			encoding.push_back(bit == '1' ? true : false);
			//- Get the char from its encoding using the tree, if the returned was void, that 
			//  means the length of the encoding vector didn't reach any leaf, so add the next 
			//  bit and try again.
			//- If it wasn't a void char, than add the char into the result string, and empty
			//  the encoding vector.
			char character = tree->getCharFromEncoding(encoding);
			if (character != '\0') {
				*decompressedString += character;
				encoding.clear();
			}
		}
		//the result after decompressing.
		return decompressedString;
	}

	// Unable to decompress properly
	return nullptr; 
}