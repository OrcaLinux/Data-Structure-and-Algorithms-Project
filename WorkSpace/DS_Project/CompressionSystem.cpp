/*****************************************************************//**
 * @file   CompressionSystem.cpp
 * @brief  The system that compresses the files.
 *
 * The file contains many static functions, use the one you need for the task.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#include "CompressionSystem.h"

bool CompressionSystem::compress_SocialNetworkXML(const std::string& file, const std::string& path)
{
	//Minify
	MinifyingXML* minifyObj = new MinifyingXML(&file);
	std::string* afterMinifying = minifyObj->minifyString();

	delete minifyObj;
	minifyObj = nullptr;

	//ClearClosingtags
	ClearClosingTagsComp* clearingObj = new ClearClosingTagsComp(afterMinifying);
	std::string* afterClearing = clearingObj->compress();

	delete clearingObj;
	clearingObj = nullptr;
	delete afterMinifying;
	afterMinifying = nullptr;

	//Tag Mapping
	TagsMapComp* mappingObj = new TagsMapComp(afterClearing);
	std::string* afterMapping = mappingObj->compress();

	delete mappingObj;
	mappingObj = nullptr;
	delete afterClearing;
	afterClearing = nullptr;

	//Huffman
	HuffmanComp* huffmanObj = new HuffmanComp(afterMapping);
	std::string* afterHuffman = huffmanObj->compress();

	delete huffmanObj;
	huffmanObj = nullptr;
	/*delete afterMapping;
	afterMapping = nullptr;*/


	bool result = saveFile(*afterHuffman, path);

	delete afterHuffman;
	afterHuffman = nullptr;

	return result;
}

bool CompressionSystem::compress_XML(const std::string& file, const std::string& path)
{
    //Minify
    MinifyingXML* minifyObj = new MinifyingXML(&file);
    std::string* afterMinifying = minifyObj->minifyString();

    delete minifyObj;
    minifyObj = nullptr;

    //Tag Mapping
    TagsMapComp* mappingObj = new TagsMapComp(afterMinifying);
    std::string* afterMapping = mappingObj->compress(true);

    delete mappingObj;
    mappingObj = nullptr;
    delete afterMinifying;
    afterMinifying = nullptr;

    //Huffman
    HuffmanComp* huffmanObj = new HuffmanComp(afterMapping);
    std::string* afterHuffman = huffmanObj->compress();

    delete huffmanObj;
    huffmanObj = nullptr;
    /*delete afterMapping;
    afterMapping = nullptr;*/


    bool result = saveFile(*afterHuffman, path);

    delete afterHuffman;
    afterHuffman = nullptr;

    return result;
}

bool CompressionSystem::compress_JSON(const std::string& file, const std::string& path)
{
    //Minify JSON
    //TODO: ask abdo
    std::string* afterMinifying;

//    delete minifyObj;
//    minifyObj = nullptr;


    //Huffman
    HuffmanComp* huffmanObj = new HuffmanComp(afterMinifying);
    std::string* afterHuffman = huffmanObj->compress();

    delete afterMinifying;
    afterMinifying = nullptr;

    delete huffmanObj;
    huffmanObj = nullptr;

    bool result = saveFile(*afterHuffman, path);

    delete afterHuffman;
    afterHuffman = nullptr;

    return result;
}

bool CompressionSystem::compress_File(const std::string& file, const std::string& path)
{
    std::string* f = new std::string(file);
    //Huffman
    HuffmanComp* huffmanObj = new HuffmanComp(f);
    std::string* afterHuffman = huffmanObj->compress();

    delete f;
    f = nullptr;
    delete huffmanObj;
    huffmanObj = nullptr;

    bool result = saveFile(*afterHuffman, path);

    delete afterHuffman;
    afterHuffman = nullptr;

    return result;
}

//TODO: the contain binary = false part.
bool CompressionSystem::saveFile(const std::string& fileComp, const std::string& path)
{
	bool result = false;
	//get the text block
	int textEnd = fileComp.find("\n", fileComp.find(")\n") + 2);
	if (textEnd == std::string::npos) {
		return false;
	}
	//write the text block (tree encoding + bits number).
	std::string text = fileComp.substr(0, textEnd + 1);

	try {
		std::ofstream file(path, std::ios::out | std::ios::binary);
		if (file.is_open()) {
			file << text;

			//bits string
			std::string bits = fileComp.substr(textEnd + 1);

			int length = bits.size();
			int numBits = length - textEnd;
			int numBytes = (numBits + 7) / 8;
			int remainingBits = 8 * numBytes - numBits;

			// Write complete bytes
			std::string currentByte;
			for (char bit : bits) {
				currentByte += bit;
				if (currentByte.size() == 8) {
					char byte = 0;
					for (int i = 0; i < 8; ++i) {
						byte |= (currentByte[i] == '1') ? (1 << (7 - i)) : 0;
					}
					file.put(byte);
					currentByte.clear();
				}
			}

			// If there are remaining bits, pad the last byte with zeros
			if (!currentByte.empty()) {
				// Extend currentByte to a full byte (if necessary)
				while (currentByte.size() < 8) {
					currentByte += '0';
				}

				char byte = 0;
				for (int i = 0; i < 8; ++i) {
					byte |= (currentByte[i] == '1') ? (1 << (7 - i)) : 0;
				}
				file.put(byte);
			}
			file.close();
			return true;
		}
	}
	catch (const std::exception& e) {
		return false;
	}
	return result;
}
