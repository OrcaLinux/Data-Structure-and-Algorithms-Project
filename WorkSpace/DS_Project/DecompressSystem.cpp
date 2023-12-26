#include "DecompressSystem.h"

std::string* DecompressSystem::readFile(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::binary);
	std::stringstream result;

	if (file.is_open()) {
		// Read text block
		std::string line;
		std::getline(file, line);
		result << line << "\n";

		// Read the number block
		std::getline(file, line);
		result << line << "\n";

		// Read the bits block
		std::stringstream bits;

		// Read the remaining content
		bits << file.rdbuf(); 
		//convert the bytes block to bits string of ones and zeros.
		std::string bitsString = bits.str();
		for (char ch : bitsString) {
			// Convert the character to its ASCII value
			int asciiValue = static_cast<int>(ch);

			// Convert ASCII value to binary representation (8 bits)
			std::bitset<8> bitset(asciiValue);
			// Iterate through each bit and add '1' or '0' to the result string
			for (int i = 7; i >= 0; --i) {
				result << (bitset[i] ? '1' : '0');
			}
		}

		file.close();
	}
	std::string* r = new std::string(result.str());
	return r;
}

std::string* DecompressSystem::decompress_SocialNetworkXML(const std::string& filePath)
{
	//read the file
	std::string* fileComp = readFile(filePath);

	//Huffman Decompress
	HuffmanDec* huffmanObj = new HuffmanDec(fileComp);
	std::string* huffmanDec = huffmanObj->decompress();

	delete huffmanObj;
	huffmanObj = nullptr;

	//Tags Mapping Decompress
	TagsMapDec* mappingDecObj = new TagsMapDec(huffmanDec);
	std::string* mapDec = mappingDecObj->decompress();

	delete mappingDecObj;
	mappingDecObj = nullptr;
	delete huffmanDec;
	huffmanDec = nullptr;

	//Clear Closing Tags Decompress
	ClearClosingTagsDec* clearingDecObj = new ClearClosingTagsDec(mapDec);
	std::string* clearingDec = clearingDecObj->decompress();

	delete clearingDecObj;
	clearingDecObj = nullptr;
	delete mapDec;
	mapDec = nullptr;

	return clearingDec;
}

std::string* DecompressSystem::decompress_XML(const std::string& filePath){
    //read the file
    std::string* fileComp = readFile(filePath);

    //Huffman Decompress
    HuffmanDec* huffmanObj = new HuffmanDec(fileComp);
    std::string* huffmanDec = huffmanObj->decompress();

    delete huffmanObj;
    huffmanObj = nullptr;

    //Tags Mapping Decompress
    TagsMapDec* mappingDecObj = new TagsMapDec(huffmanDec);
    std::string* mapDec = mappingDecObj->decompress();

    delete mappingDecObj;
    mappingDecObj = nullptr;
    delete huffmanDec;
    huffmanDec = nullptr;

    return mapDec;
}

std::string* DecompressSystem::decompress_File(const std::string& filePath){
    //read the file
    std::string* fileComp = readFile(filePath);

    //Huffman Decompress
    HuffmanDec* huffmanObj = new HuffmanDec(fileComp);
    std::string* huffmanDec = huffmanObj->decompress();

    delete huffmanObj;
    huffmanObj = nullptr;


    return huffmanDec;
}


std::string* DecompressSystem::decompress_JSON(const std::string& filePath){
    //read the file
    std::string* fileComp = readFile(filePath);

    //Huffman Decompress
    HuffmanDec* huffmanObj = new HuffmanDec(fileComp);
    std::string* huffmanDec = huffmanObj->decompress();

    delete huffmanObj;
    huffmanObj = nullptr;


    return huffmanDec;
}
