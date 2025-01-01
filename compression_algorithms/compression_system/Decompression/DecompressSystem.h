/*****************************************************************//**
 * @file   DecompressSystem.h
 * @brief  The system that decompresses the files.
 * 
 * The file contains many static functions, use the one you need for the task.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#pragma once
#ifndef DECOMPRESS_SYSTEM_H
#define DECOMPRESS_SYSTEM_H

#include <fstream>
#include <sstream>
#include <bitset>
#include "HuffmanDec.h"
#include "ClearClosingTagsDec.h"
#include "TagsMapDec.h"

class DecompressSystem
{
public:
	/**
	 * @brief Reads a Huffman compressed file and returns a string contains the data as physical bits.
	 * 
	 * The file might contain extra bits and the end, so don't forget to use the number of bits in the 
	 * 2nd line to get the only needed bits.
	 * 
	 * @param filePath  Path of the output file + file name and extension. 
	 * @return A pointer to a string of the file.
	 */
	static std::string* readFile(const std::string& filePath);
	/**
	 * @brief Decompresses a social network XML file..
	 * 
	 * It will read the file using std::string* readFile(const std::string& filePath) method.
	 * It apply these algorithms on the read file string in order:
	 * -Huffman Decompress.
	 * -Tags Mapping Decompress.
	 * -Clear Closing Tags Decompress.
	 * 
	 * @param filePath Path of the output file + file name and extension. 
	 * @return A pointer to a string that contains the decompressed file.
	 */
	static std::string* decompress_SocialNetworkXML(const std::string& filePath);

    /**
     * @brief Decompresses a social network XML file..
     *
     * It will read the file using std::string* readFile(const std::string& filePath) method.
     * It apply these algorithms on the read file string in order:
     * -Huffman Decompress.
     * -Tags Mapping Decompress.
     *
     * @param filePath Path of the output file + file name and extension.
     * @return A pointer to a string that contains the decompressed file.
     */
    static std::string* decompress_XML(const std::string& filePath);

    /**
     * @brief Decompresses a social network XML file..
     *
     * It will read the file using std::string* readFile(const std::string& filePath) method.
     * It apply these algorithms on the read file string in order:
     * -Huffman Decompress.
     *
     * @param filePath Path of the output file + file name and extension.
     * @return A pointer to a string that contains the decompressed file.
     */
    static std::string* decompress_JSON(const std::string& filePath);

    /**
     * @brief Decompresses a social network XML file..
     *
     * It will read the file using std::string* readFile(const std::string& filePath) method.
     * It apply these algorithms on the read file string in order:
     * -Huffman Decompress.
     *
     * @param filePath Path of the output file + file name and extension.
     * @return A pointer to a string that contains the decompressed file.
     */
    static std::string* decompress_File(const std::string& filePath);
};

#endif // !DECOMPRESS_SYSTEM_H

