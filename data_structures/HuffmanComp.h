/*****************************************************************//**
 * @file   HuffmanComp.h
 * @brief  Header file for Huffman Compression algorithm.
 *
 * This file defines the HuffmanComp class, which implements Huffman compression.
 * It utilizes HuffmanTree for encoding and generates compressed output
 * based on the Huffman tree's encoded representation.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/


#pragma once
#ifndef HUFFMAN_COMP_H
#define HUFFMAN_COMP_H
#include "HuffmanTree.h"

class HuffmanComp
{
private:
	// tree holds the encoding.
	HuffmanTree* tree;
	//the file to compress.
	std::string* file;

public:
	/**
	 * @brief C'tor.
	 * 
	 * It will construct the tree from the HuffmanTree::generateTreeFromText()
	 * static method.
	 * 
	 * @param fileC file to compress
	 */
	explicit HuffmanComp(std::string* fileC) : file(fileC) {
		this->tree = HuffmanTree::generateTreeFromText(*fileC);
	}

	/**
	 * @brief D'tor.
	 */
    ~HuffmanComp() { delete tree;
        //delete file;
    }

	/**
	 * @brief Compresses the file content using the Huffman tree.
	 *
	 * This function compresses the file content using the Huffman tree's encoded representation.
	 * It encodes each character in the file content using the Huffman tree and returns
	 * a pointer to the compressed string.
	 *
	 * @return A pointer to the compressed string of zeros and ones according to the encoding 
	 * of each char.
	 */
	std::string* compress();
};

#endif // !HUFFMAN_COMP_H
