/*****************************************************************//**
 * @file   CompressionSystem.h
 * @brief  The system that compresses the files.
 * 
 * The file contains many static functions, use the one you need for the task.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#pragma once

#ifndef COMPRESSION_SYSTEM_H
#define COMPRESSION_SYSTEM_H

#include "MinifyingXML.h"
#include "ClearClosingTagsComp.h"
#include "TagsMapComp.h"
#include "HuffmanComp.h"
#include <fstream>

class CompressionSystem
{
public:
	/**
	 * @brief Compresses a social network XML file.
	 * 
	 * It apply these algorithms in order:
	 * - Minifying XML.
	 * - Clear Closing Tags.
	 * - Tag Mapping.
	 * - Huffman Encoding.
	 * 
	 * Then saves the result file into the passed path with file name.
	 * using saveFile(const std::string& file, const std::string& path); method.
	 * 
	 * @param file File to compress.
	 * @param path path of the output file + file name and extension.
     * E.g., ".../path to the file/file name.sncxml"
	 * @return true if the operation succeed. 
	 */
    static bool compress_SocialNetworkXML(const std::string& file, const std::string& path);

    /**
     * @brief Compresses any correct XML file.
     *
     * It apply these algorithms in order:
     * - Minifying XML.
     * - Tag Mapping.
     * - Huffman Encoding.
     *
     * Then saves the result file into the passed path with file name.
     * using saveFile(const std::string& file, const std::string& path); method.
     *
     * @param file File to compress.
     * @param path path of the output file + file name and extension.
     * E.g., ".../path to the file/file name.cxml"
     * @return true if the operation succeed.
     */
    static bool compress_XML(const std::string& file, const std::string& path);

    /**
     * @brief Compresses any correct XML file.
     *
     * It apply these algorithms in order:
     * - Minifying JSON.
     * - Huffman Encoding.
     *
     * Then saves the result file into the passed path with file name.
     * using saveFile(const std::string& file, const std::string& path); method.
     *
     * @param file File to compress.
     * @param path path of the output file + file name and extension.
     * E.g., ".../path to the file/file name.cjson"
     * @return true if the operation succeed.
     */
    static bool compress_JSON(std::string& file, const std::string& path);

    /**
     * @brief Compresses any correct XML file.
     *
     * It apply these algorithms in order:
     * - Huffman Encoding.
     *
     * Then saves the result file into the passed path with file name.
     * using saveFile(const std::string& file, const std::string& path); method.
     *
     * @param file File to compress.
     * @param path path of the output file + file name and extension.
     * E.g., ".../path to the file/file name.cfile"
     * @return true if the operation succeed.
     */
    static bool compress_File(const std::string& file, const std::string& path);

	/**
	 * @brief Saves the Huffman encoded (compressed) string to the required path..
	 * 
	 * @param file Compressed file.
	 * @param path  Path of the output file + file name and extension. 
	 * @return true if the operation succeed. 
	 */
	static bool saveFile(const std::string& file, const std::string& path);


};

#endif // !COMPRESSION_SYSTEM_H
