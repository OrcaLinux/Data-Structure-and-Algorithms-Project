/*****************************************************************//**
 * @file   TagsMapComp.cpp
 * @brief  The source file of TagsMapComp class.
 *
 * A compression algorithm that maps tags into numbers.
 * By applying this algorithm, the size file decrease, as many characters in
 * tags will be getting red off, so theses char will not repeated over and over again.
 *
 * To now the mapping values, a <TagsMap> block will be added to the start of the
 * XML file.
 *
 * Example:
 * -> File before:
 * <tag0><tag1><tag2></tag2><tag2></tag2></tag1></tag0>
 *
 * -> File after:
 * <TagMap>tag0,tag1,tag2<Tag/Map>
 * <t0><t1><t2></t2><t2></t2></t1></t0>
 *
 * @note: <TagMap> block is optional, Will not be added to the social network
 * file, is tags are constant there.
 *
 * @note: if <TagMap> is added, this algorithm will be efficient only if it contains lots of
 * long tags.
 * @note all methods in this class assumes that the input file is flawless.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "TagsMapComp.h"

void TagsMapComp::mapTags()
{
	std::stringstream ss(*this->xmlFile);
	std::string tag;
	std::string line;

	while (std::getline(ss, line, '<')) {
		// Trim leading spaces
		line.erase(0, line.find_first_not_of(" \t\n\r"));
		// Extract the tag name between '<' and '>'
		int pos = line.find('>');
		if (pos == -1) {
			continue;
		}
		int start = 0;
		//closing tag
		if (line.at(0) == '/') {
			start = 1;
		}
		int length = pos - start;
		tag = line.substr(start, length);

		// If the tag wasn't in the map, add it
		if (!map->containKey(&std::string(tag))) {
			map->add(new std::string(tag));
		}
	}
}

std::string* TagsMapComp::compress(bool addMapTable)
{
	//to store the result.
	std::string* result = new std::string();
	//length of the original file.
	int length = this->xmlFile->size();

	//
	// The max size of the result string is the same of the entered string.
	// That happens when the original doesn't contain any extra spaces or
	// other charToSkip elements.
	// // the added 60 is for the mapTable.
	//
	result->reserve(length + 60);

	//add MapTable if required
	if (addMapTable) {
		std::string* mapTags = map->toString();
		result->append(*mapTags);
		result->append(1, '\n');

		delete mapTags;
		mapTags = nullptr;
	}

	/*
	* Loop for all the original string.
	* - If the current string is '<'
	*		1.Collect the tag after it.
	*		2.Map that tag.
	*		3.Add the mapped tag to the result string.
	* - For other characters, add them to the result.
	*/
	char currentChar = 0;
	for (int i = 0; i < length; i++) {
		// get current char
		currentChar = this->xmlFile->at(i);

		//current char is '<' --> map the tag.
		if (currentChar == '<') {
			// increment the counter to get the next char.
			i++;
			// get the next char
			currentChar = this->xmlFile->at(i);

			// to know it is an opening or closing tag.
			bool openingTag = true;
			if (currentChar == '/') {
				openingTag = false;
				// increment the counter to get the next char.
				i++;
				// get the next char
				currentChar = this->xmlFile->at(i);
			}

			// To store the tag.
			std::string tag = std::string();
			//loop to get the full tag
			while (currentChar != '>') {
				// append it to the tag string
				tag.append(1, currentChar);
				// increment the counter.
				i++;
				// get current char
				currentChar = this->xmlFile->at(i);
			}

			//map the tag
			std::string afterMaping = std::string("<");
			if (!openingTag) {
				afterMaping.append("/");
			}
			afterMaping.append(1, 't');
			afterMaping.append(std::to_string(map->getValue(&tag)));
			afterMaping.append(1, '>');

			//append to the result.
			result->append(afterMaping);
		} // if current char == '<'

		else {
			result->append(1, currentChar);
		}
	}

	// Free the extra allocated memory locations.
	result->shrink_to_fit();
	return result;
}// compress()