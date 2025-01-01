/*****************************************************************//**
 * @file   Map.cpp
 * @brief  The source file of the simple Map.
 * 
 * This a simple implementation of Map data structure that will help Mapping
 * tags into numbers.
 * Each tag will mapped into the value of its position in the vector.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "Map.h"

void Map::trimString(std::string& str)
{
	str.erase(0, str.find_first_not_of(' ')); // Remove leading spaces
	str.erase(str.find_last_not_of(' ') + 1); // Remove trailing spaces
}

Map::Map(const std::string* tagMapBlock)
{
	this->arr = new std::vector<std::string*>();
	//clear the spaces of the file.
	MinifyingXML* m = new MinifyingXML(tagMapBlock);
	std::string* afterMini = m->minifyString();
	delete m;
	m = nullptr;

	// Get the positions of the opening and closing tags to remove them
	int openingTagPos = afterMini->find("<TagMap>");
	int closingTagPos = afterMini->find("</TagMap>");

	//check that the tag is available.
	if (openingTagPos == std::string::npos
		|| closingTagPos == std::string::npos) {
		throw std::runtime_error("Defected TagMAp block");
	}

	//erase the tag
	// Erase the opening tag "<TagMap>"
	afterMini->erase(openingTagPos, 8); 
	// Erase the closing tag "</TagMap>"
	afterMini->erase(afterMini->size() - 9, 9); 

	// add the values between ',' into the arr vector.
	std::stringstream ss(*afterMini);
	std::string* token = new std::string();

	while (std::getline(ss, *token, ',')) {
		Map::trimString(*token);
		this->add(token);
		token = new std::string();
	}
	delete token;
	token = nullptr;

	delete afterMini;
	afterMini = nullptr;
}

int Map::add(std::string* key)
{
	arr->push_back(key);
	return arr->size() - 1;
}

int Map::getValue(const std::string* key) const
{
	int counter = -1;
	for (int i = 0; i < arr->size(); i++) {
		std::string* k = arr->at(i);
		if (*k == *key) {
			return i;
		}
	}
	return -1;
}

const std::string* Map::getKey(int value) const
{
	if (arr->size() == 0) {
		throw std::runtime_error("array out of bound exception");
	}
	if (value < 0 || value> arr->size() - 1) {
		throw std::runtime_error("array out of bound exception");
	}
	return arr->at(value);
}

bool Map::containKey(const std::string* key) const {
	return (this->getValue(key) == -1) ? false : true;
}

std::string* Map::toString()
{
	if (arr->size() == 0) {
		throw std::runtime_error("No value are being mapped");
	}
	std::string* result = new std::string("<TagMap>");
	for (std::string* s : *arr) {
		result->append(*s);
		result->append(",");
	}
	result->erase(result->size() - 1);
	result->append("</TagMap>");
	return result;
}