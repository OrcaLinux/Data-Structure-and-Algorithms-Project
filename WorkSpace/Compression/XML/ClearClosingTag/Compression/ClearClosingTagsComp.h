/*****************************************************************//**
 * @file   ClearClosingTagsComp.h
 * @brief  The header file of ClearClosingTagsComp class.
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
 * @Warning This implementation only works for Social network system, needs an update.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef CLEAR_CLOSING_TAGS_COMP_H
#define CLEAR_CLOSING_TAGS_COMP_H

#include <string>

class ClearClosingTagsComp
{
private:
	const std::string* xmlFile;

public:
	/**
	 * @brief C'tor.
	 *
	 * Initializes the XML file.
	 *
	 * @param  the XML file without the XML version and encoding line.
	 */
	explicit ClearClosingTagsComp(const std::string* xmlFile) : xmlFile(xmlFile) {}

	/**
	 * @brief This function compresses the XML file..
	 *
	 * Operation summary:
	 * - Find the closing tag.
	 * - Delete the closing tag.
	 *
	 * @return The result string doesn't contain XML version and encoding line.
	 *
	 * @Warning use only with social network data.
	 */
	std::string* compress();
}; // class ClearClosingTagsComp
#endif // !CLEAR_CLOSING_TAGS_COMP_H
