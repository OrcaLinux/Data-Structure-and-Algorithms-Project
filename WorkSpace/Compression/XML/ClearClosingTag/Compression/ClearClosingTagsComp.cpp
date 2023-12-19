/*****************************************************************//**
 * @file   ClearClosingTagsComp.cpp
 * @brief  The source file of ClearClosingTagsComp class.
 *
 * - This algorithm of compression is based on deleting all the ending tags
 *   to reduce the space of the xmlFile.
 * - It requires knowing what tags comes after other to know how to decompress
 *   the file.
 *
 * Example:
 * - File before:
 * <tag0><tag1><tag2>d1</tag2><tag2>d2</tag2></tag1></tag0>
 *
 * - File after:
 * <tag0><tag1><tag2>d1<tag2>d2
 *
 * @TODO update the file to work with any type of XML data. Use Trees to
 * recored the order of the tags.
 *
 * @warning This implementation only works for Social network system, needs an update.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "ClearClosingTagsComp.h"

std::string* ClearClosingTagsComp::compress()
{
	// to store the result.
	std::string* result = new std::string();
	//length of the original file.
	int length = this->xmlFile->size();

	// The max size of the result string is the same of the entered string.
	result->reserve(length);

	/*
	* Loop for all the original string.
	* - If the current string is '</'
	*		1.skip that tag (increment i till the end of the tag).
	*		2.Don't add it to the result string.
	* - For other characters, add them to the result.
	*/
	char currentChar = 0;
	for (int i = 0; i < length; i++) {
		// get current char
		currentChar = this->xmlFile->at(i);
		if (currentChar == '<' && this->xmlFile->at(i + 1) == '/') {
			//skip the closing tag
			i = this->xmlFile->find('>', i);
			continue;
		}
		result->append(1, currentChar);
	}

	// Free the extra allocated memory locations.
	result->shrink_to_fit();
	return result;
}// compress()