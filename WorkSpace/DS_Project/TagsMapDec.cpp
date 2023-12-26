/*****************************************************************//**
 * @file   TagsMapDec.cpp
 * @brief  The header file of TagsMapDec class.
 *
 * The decompression algorithm of TagsMap compression algorithm.
 * The decompression will re-map the tags to their original value.
 *
 * The file might contain a TagsMap tag at the beginning, from that tag we can
 * get the mapping numbers.
 *
 * If the file doesn't contain this tag, then it will be assumed to be:
 * <TagMap>users,user,id,name,posts,post,body,topics,topic,followers,follower</TagMap>.
 * which will be used for social network system only.
 *
 * Example:
 * -> File before:
 * <TagMap>tag0,tag1,tag2<Tag/Map>
 * <0><1><2></2><2></2></1></0>
 *
 * -> File after:
 * <tag0><tag1><tag2></tag2><tag2></tag2></tag1></tag0>
 *
 * @see TagsMapComp
 * @author eslam
 * @date   December 2023
 *********************************************************************/

 #include "TagsMapDec.h"

void TagsMapDec::getMapTags()
{
	const std::string* tagMapLine = this->getTagsMapBlock();
	this->map = new Map(tagMapLine);
	if (tagMapLine != defualtTagMapBlock) {
		delete tagMapLine;
		tagMapLine = nullptr;
	}
}

const std::string* TagsMapDec::getTagsMapBlock()
{
	//Minify the file
	MinifyingXML* m = new MinifyingXML(this->xmlFile);
	std::string* afterMinifying = m->minifyString();
	//deallocate m
	delete m;
	m = nullptr;

	//get the position of both the opening and the closing tags
	int start = afterMinifying->find("<TagMap>");
	int end = afterMinifying->find("</TagMap>");
	//if any was not found, then the file is assumed to be for
	//social network system --> return the default line
	if (start == std::string::npos && end == std::string::npos) {
		return defualtTagMapBlock;
	}

	//if tagMap wasn't in the first position, then the file is defected
	else if (start != 0) {
		throw std::runtime_error("Defected file.");
	}

	//get the line and return it.
	const std::string* result = new std::string(
		afterMinifying->substr(start, end + 9 - start)
	);
	//deallocate after minifying string.
	delete afterMinifying;
	afterMinifying = nullptr;
	return result;
}// getTagsMapBlock()

std::string* TagsMapDec::decompress()
{
	//to store the result.
	std::string* result = new std::string();
	//length of the original file.
	int length = this->xmlFile->size();
	// Assume that the worst case will be triple the size.
	result->reserve(length * 3);

	//skip the TagMap block
	int i = this->xmlFile->find("</TagMap>");
	// if the block is not found, start from the beginning.
	if (i == std::string::npos) {
		i = 0;
	}
	else {
		i += 9;
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
	for (i; i < length; i++) {
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

			// To store the tag number.
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
			//get the number from the tag
			int value = std::stoi(tag);

			//map the tag
			std::string afterMaping = std::string("<");
			if (!openingTag) {
				afterMaping.append("/");
			}

			afterMaping.append(*map->getKey(value));
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
}// decompress()