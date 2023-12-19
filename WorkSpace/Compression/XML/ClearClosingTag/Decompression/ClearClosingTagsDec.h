/*****************************************************************//**
 * @file   ClearClosingTagsDec.h
 * @brief  The header file of ClearClosingTagsDec class.
 *
 * - The decompression algorithm is based on returning the removed tags from compression.
 * - It requires knowing what tags comes after other to know how to decompress the file.
 * 
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

#pragma once
#ifndef CLEAR_CLOSING_TAGS_DEC_H
#define CLEAR_CLOSING_TAGS_DEC_H

#include "Tree.h"
#include <stack>

class ClearClosingTagsDec
{
private:
	//Holds the known arrange of tags.
	Tree* tagsTree;
	//To know which tag we are inside.
	std::stack<const TreeNode*>* tagsStack;
	//The file needed to be decompressed.
	const std::string* xmlFile;

	//helper methods
	/**
	 * @brief get the tag string starting from the position of '<' till '>'.
	 * 
	 * @param tagPosition position of '<' of the needed tag.
	 * @return the tag as a string.
	 * @warning Don't forget to deallocate the input string after decompression.
	 */
	std::string getTag(int& tagPosition) const;
	/**
	 * @brief Determine whether the tag needs a closing tag of the prev tag or not.
	 * 
	 * Based on the top of the stack and the tree, we determine the result.
	 * Operation summary:
	 * - Call the function when we reach a new tag.
	 * - If the stack was empty, then the passed tag is the first tag in the file.
	 * - If the stack wasn't empty, get the top tag on the stack, and check if it has the 
	 * passed tag as a children of it or not, if yes return false, as we will not need to add 
	 * a closing string after the tag.
	 * - If it wasn't a child, return true to add the closing tag.
	 * @note This method doesn't arr the closing tag, nor pops the stack, you will have to do that for the true returned result.
	 * 
	 * Example:
	 * - The input: <users><user><id>0<name>
	 * --First tag <users> will be passed to the function, we cam see that the stack is empty, the function will push the tag into 
	 * the stack return false.
	 * -- <user> passed: it will check the top of stacks children in the tree, which is true, so it  will push the tag into 
	 * the stack return false.
	 * -- <id>: same as <user>.
	 * -- <name>: is not a child of <id>, so it will return false, and the caller of the function must pop the stack, add an ening tag
	 * for <id> which is </id>, and recall this function with the same tag, now it will check if <name> is a child of <user> which will be the 
	 * same case as in <user> and <id>.
	 * 
	 * @param tag the new tag.
	 * @return bool whether to add a closing tag or not.
	 */
	bool needClosingTag(std::string& tag) const;

public:
	/**
	 * @brief C'tor that initializes the XML string with provided value,
	 * and empty tagsTree, and empty tagsStack.
	 * 
	 * XML version and encoding line example:
	 * @verbatim
	   <?xml version="1.0" encoding="UTF-8"?>
	 * @endverbatim
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
	 * @warning use only with social network data.
	 */
	std::string* decompress() const;
};

#endif // !CLEAR_CLOSING_TAGS_DEC_H
