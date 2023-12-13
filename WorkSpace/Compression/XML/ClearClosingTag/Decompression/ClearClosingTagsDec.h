/*****************************************************************//**
 * @file   ClearClosingTagsDec.h
 * @brief  The header file of ClearClosingTagsDec class.
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
 * @Warning This implementation only works for Social network system, needs an update.
 *
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef CLEAR_CLOSING_TAGS_DEC_H
#define CLEAR_CLOSING_TAGS_DEC_H

#include "Tree.h"
#include <stack>

class ClearClosingTagsDec
{
private:
	Tree* tagsTree;
	std::stack<const TreeNode*>* tagsStack;
	const std::string* xmlFile;

	//helper methods

	std::string getTag(int& tagPosition) const;
	bool needClosingTag(std::string& tag) const;

public:
	/**
	 * @brief C'tor that initializes the XML string with provided value,
	 * and empty tagsTree, and empty tagsStack.
	 * 
	 * @param the XML file without the XML version and encoding line.
	 */
	explicit ClearClosingTagsDec(const std::string* xmlFile) : xmlFile(xmlFile),
	tagsTree(new Tree()), tagsStack(new std::stack<const TreeNode*>()) {}
	/**
	 * @brief D'tor.
	 * 
	 */
	~ClearClosingTagsDec() { delete tagsTree; delete tagsStack; }

	/**
	 * @brief @brief This function decompresses the XML file.
	 * 
	 * Operation summary:
	 * - collect each opening tag in the stack.
	 * - when reaching a new tag, check from the tree if the current tag
	 * (in top of the stack) contains the next tag as a child this don't close the
	 * current tag, and add the next tag into the stack.
	 * - if it wasn't a child, add a closing tag for the current tag, then check the same with the 
	 * next value in the stack.
	 * - At the end add all the remaining tags in the stack in their order.
	 * 
	 * @return The result string doesn't contain XML version and encoding line.
	 * 
	 * @Warning use only with social network data.
	 */
	std::string* decompress() const;
};

#endif // !CLEAR_CLOSING_TAGS_DEC_H
