/*****************************************************************//**
 * @file   MinifyingXML.h
 * @brief  Header file of the MinifyingXML class.
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
 *	  i.e., "<tagg> value with spaces </tagg>" --apply minifying--> "<tagg>value with spaces</tagg>",
 *	  on other words, the value will be trimmed from spaces before or after it.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#pragma once
#ifndef MINIFYING_XML_H
#define MINIFYING_XML_H
#include <string>

#include <stdexcept>

class MinifyingXML
{
private:
	// the file that neads to be minified.
	const std::string* xmlFile;

	// char To skip in minifying.
	static const char charToSkip[5];

public:
	/**
	 * @brief C'tor
	 *
	 * @see D'tor, this class will not deallocate the XML file string.
	 * @param xmlFile
	 */
	explicit MinifyingXML(const std::string* xmlFile) : xmlFile(xmlFile) {
		// check adding a null ptr.
		if (xmlFile == nullptr) {
			throw std::logic_error("Null pointer exception: Accessing null pointer!");
		}
	}

	//methods

	/**
	* @brief This function deletes any spaces and new lines from the XML File.
	*
	* It removes any charToSkip from the file string, except spaces in the tags values
	* (leading and trailing spaces are removed from the value too).
	*
	* @see  MinifyingXML::charToSkip array.
	*
	* @return The result string from minifying function.
	*/
	std::string* minifyString();

	/**
	 * @brief function checks if the char is one the located characters.
	 *
	 * @param c -The character to check.
	 * @return  - True if it's a skip char.
	 * - False otherwise.
	 *
	 * @see MinifyingXML::charToSkip array.
	 */
	static bool isSkipChar(const char c);

	//helper methods

	/**
	 * @brief This function clears all the skip Chars except some spaces.
	 *
	 * Operation:
	 * - For all the string, skip (don't add it into the result) all charToskip elements except spaces.
	 * - For space cases:
	 * -> Starting from the beginning, skip any spaces until reaching the first closing tag '>'.
	 * -> After the closing tab, skip any spaces until reaching the first non skip value (any
	 *	 chars not in charToSkip array).
	 * -> Add all spaces until reaching the next opening tag '<'.
	 *
	 * Example: "   <name> Ahmed Ali  \n </name>"
	 *			--> "<name>Ahmed Ali   </name>"
	 *
	 * @param result an empty string to store the result of this function.
	 */
	void skipFromBeginning(std::string* result)const;

	/**
	* @brief This function clears the extra spaces left from the prev step.
	*
	* Operation:
	* Starting from the last element.
	* - Clear all the spaces before any opening tag '<' till the prev last non skip char.
	* -> If the current element was the opening tag, skip spaces.
	* -> If the current element is any non skip char, stop skipping spaces.
	*
	* Example: "<name>Ahmed Ali   </name>"
	*			--> "<name>Ahmed Ali</name>"
	*
	* - Other skip chars are eliminated from the prev step.
	*
	* @see void MinifyingXML::skipFromBeginning(std::string* result).
	*
	* @param result The result string from the prev step to modify it.
	*/
	void skipFromEnd(std::string* result) const;

	//getters and setters, used for debugging
	//getters.

	//XML file getter.
	const std::string* getXMLFile() const { return this->xmlFile; }

	//setters
	//XML file setter.
	void setXMLFile(const std::string* xmlFileNew) {
		// check adding a null ptr.
		if (xmlFileNew == nullptr) {
			throw std::logic_error("Null pointer exception: Accessing null pointer!");
		}
		this->xmlFile = xmlFileNew;
	}
}; //class MinifyingXML

#endif // !MINIFYING_XML_H