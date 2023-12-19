/*****************************************************************//**
 * @file   ClearClosingTagsDec.cpp
 * @brief  The source file of ClearClosingTagsDec class.
 *
 * - The decompression algorithm is based on returning the removed tags from compression.
 * - It requires knowing what tags comes after other to know how to decompress
 *   the file.
 * Example:
 * - File before:
 * <tag0><tag1><tag2>d1<tag2>d2
 *
 * - File after:
 * <tag0><tag1><tag2>d1</tag2><tag2>d2</tag2></tag1></tag0>
 *
 * @TODO update the file to work with any type of XML data. Use Trees to
 * recored the order of the tags.
 *
 * @warning This implementation only works for Social network system, needs an update.
 *
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "ClearClosingTagsDec.h"

std::string ClearClosingTagsDec::getTag(int& tagPosition) const
{
	//get the '<'
	char currentChar = this->xmlFile->at(tagPosition);
	//append '<' to the result string.
	std::string tag = std::string(1, currentChar);
	//loop and add all chars to the result until '>'
	while (currentChar != '>') {
		tagPosition++;
		currentChar = this->xmlFile->at(tagPosition);
		tag += currentChar;
	}
	return tag;
}

bool ClearClosingTagsDec::needClosingTag(std::string& tag) const
{
	if (tagsStack->empty()) {
		tagsStack->push(tagsTree->getRoot());
		return false;
	}
	bool isChild = tagsStack->top()->isChild(&tag.substr(1, tag.length() - 2));
	if (isChild) {
		tagsStack->push(tagsStack->top()->getChild(&tag.substr(1, tag.length() - 2)));
		return false;
	}
	else {
		return true;
	}
}

std::string* ClearClosingTagsDec::decompress() const
{
	// to store the result.
	std::string* result = new std::string();
	//length of the original file.
	int length = this->xmlFile->size();

	// Reserve double the space of the original string.
	result->reserve(2 * length);

	/*
	* Loop for all the original string.
	* - If the current string is '<' collect that tag then:
	*		1.If the stack is empty, add the tag's node into the stack.
	*		2.else check the top tag on the stack
	*			a.If the current is a child of the top tag:
	*			  add the current tag to the stack, and to the result string.
	*			b.if it's not pop the op tag and append it to the result
	*			  as a closing tag.
	*			  Repeat that till the current tag is a child of the top tag,
	*			  then do the same as in a.
	*		3.At the end of the file add all the remaining tags in the stack as
	*		  a closing tags in order.
	* - For other characters, add them to the result.
	*/
	char currentChar = 0;
	for (int i = 0; i < length; i++) {
		// get current char
		currentChar = this->xmlFile->at(i);
		if (currentChar == '<') {
			//get the tag
			std::string tag = getTag(i);
			//check if the prev tag needs a closing tag.
			bool addClosingTag = needClosingTag(tag);
			//loop and add closing tags for the top of the stacks until addClosingTag == false.
			while (addClosingTag) {
				const TreeNode* temp = tagsStack->top();
				//get the closing tag
				std::string value = std::string(temp->getValue());
				std::string closingTag("</");
				closingTag.append(value);
				closingTag.append(">");
				result->append(closingTag);

				tagsStack->pop();

				//check the next top of stack
				addClosingTag = needClosingTag(tag);
			}
			//append the new tag.
			result->append(tag);
		} // if (currentChar == '<')
		else {
			result->append(1, currentChar);
		}
	}

	//add the remaining tags in the stack
	while (!tagsStack->empty()) {
		const TreeNode* temp = tagsStack->top();

		// get the closing tag and add it to the result
		std::string value = std::string(temp->getValue());
		std::string closingTag("</");
		closingTag.append(value);
		closingTag.append(">");

		result->append(closingTag);

		tagsStack->pop();
	}

	// Free the extra allocated memory locations.
	result->shrink_to_fit();
	return result;
}