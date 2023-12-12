/*****************************************************************//**
 * @file   MinifyingXML.cpp
 * @brief  The source file of class MinifyingXML.
 *
 * Minifying is one of the required functions in the data structure and algorithms
 * course's project.
 * Minifying is a way of decreasing the size of the file by deleting all spaces, tabs, new lines.
 *
 * This class will minify any flawless XML file.
 *
 * Operation summary:
 *	- Using the array charToSkip.
 *	- All charToSkip (except the space : ' ') will not be added into the result array.
 *	- Spaces will be added to the result string only if it occurred inside the tag's value,
 *	  not before or after the value.
 *	  i.e., "<tagg> value with spaces </tagg>"
 *	  --apply minifying--> "<tagg>value with spaces</tagg>",
 *	  on other words, the value will be trimmed from spaces before or after it.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#include "pch.h"
#include "MinifyingXML.h"

 // char To skip in minifying.
const char MinifyingXML::charToSkip[5] = { ' ', '\n', '\t','\v','\f' };

std::string* MinifyingXML::minifyString()
{
	// To store the result.
	std::string* result = new std::string();
	// Length of the original string
	int length = this->xmlFile->size();
	//
	// The max size of the result string is the same of the entered string.
	// That happens when the original doesn't contain any extra spaces or
	// other charToSkip elements.
	//
	result->reserve(length);

	this->skipFromBeginning(result);
	this->skipFromEnd(result);

	// Free the extra allocated memory locations.
	result->shrink_to_fit();
	//return the result.
	return result;
}

// TODO: check whether to add the new line too or not if it was in the body value.
// TODO: check whether to delete comments or not.

void MinifyingXML::skipFromBeginning(std::string* result) const
{
	// Length of the original string
	int length = this->xmlFile->size();
	// Flag for skipping spaces.
	bool skipSpaces = true;

	/*
	* Loop for all values starting form 0.
	* That will help removing any charToSkip after tags, but it will
	* miss the spaces after values and the next tag (starting or ending).
	*/
	// @TODO: check whether to add the new line too or not if it was in the body value.

	// To store the value of the current char on this loop.
	char currentChar = 0;
	for (int i = 0; i < length; i++) {
		//get the current element
		currentChar = this->xmlFile->at(i);

		//check if it was a skip char
		if (MinifyingXML::isSkipChar(currentChar)) {
			// @TODO if we should  add new spaces to, change the condition here.
			// If it was a space and skipSpaces is false, add the space to the result string.
			if (currentChar == ' ' && !skipSpaces) {
				result->append(1, currentChar);
			}
		}
		else {
			// If not add too the result
			result->append(1, currentChar);
			// If it was a '>' or  '<',
			// skip the next spaces.
			if (currentChar == '<' || currentChar == '>') {
				skipSpaces = true;
			}
			// else if it was any char, don't skip after it.
			else {
				skipSpaces = false;
			}
		}
	}
}

void MinifyingXML::skipFromEnd(std::string* result) const
{
	// Length of the original string
	int length = result->size();
	// Flag for skipping spaces.
	bool skipSpaces = true;

	/*
	* Loop for all values starting form the end (length - 1).
	*/
	// To store the value of the current char on this loop.
	char currentChar = 0;
	for (int i = length - 1; i >= 0; i--) {
		//get the current element
		currentChar = result->at(i);
		//if a skip space delete it.
		if (currentChar == ' ' && skipSpaces) {
			result->erase(i, 1);
		}

		//if it is a '<', set skip to true.
		else if (currentChar == '<') {
			skipSpaces = true;
		}

		// if any other char, set skip to false.
		else {
			skipSpaces = false;
		}
	}
}

bool MinifyingXML::isSkipChar(const char c)
{
	for (char ch : MinifyingXML::charToSkip) {
		if (c == ch) {
			return true;
		}
	}
	return false;
}