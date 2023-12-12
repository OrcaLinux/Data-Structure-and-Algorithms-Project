/*****************************************************************//**
 * @file   TagsMapComp.h
 * @brief  The header file of TagsMapComp class.
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

#pragma once
#ifndef TAGS_MAP_Comp_H
#define TAGS_MAP_Comp_H

#include <string>
#include "Map.h"

class TagsMapComp
{
private:
	const std::string* xmlFile;
	const static std::string* defualtTagMapBlock;
	//Map of tag values.
	Map* map;
public:
	/**
	 * @brief C'tor.
	 *
	 * Initializes the XML file, reads it and create a map with all
	 * the tags.
	 *
	 * @param xmlFile
	 */
	explicit TagsMapComp(const std::string* xmlFile) : xmlFile(xmlFile),
		map(new Map()) {
		mapTags();
	}
	/**
	 * @brief D'tor.
	 *
	 */
	~TagsMapComp() { delete map; }
	/**
	 * @brief Reads the XML file and create the map with all the tags.
	 *
	 * Explanation:
	 *	- Find the next tag.
	 *	- If the tag is in the map, do nothing.
	 *  - If the tag is not in the map add it.
	 */
	void mapTags();

	/**
	 * @brief This function compresses the XML file.
	 *
	 * Operation:
	 *	- If addMapTable is true, it adds the <TagMap> block in the first line in the string.
	 *	  Will not added otherwise (is false by default).
	 *  - It replaces all the tags (closing and opening) with
	 *	  there mapped value in the map, it also adds 't' before the number
	 *	  just for the rules of XML files.
	 * Example: <TagEg> --> <t0>, </TagEg> --> </t0>
	 *
	 * @param addMapTable if true, then a <TagMap> block will be added in the 1st
	 * line in the result string.
	 * @return A string contains the XML file after the compression.
	 *
	 * @note The result string doesn't contain XML version and encoding line.
	 */
	std::string* compress(bool addMapTable = false);
};

#endif // !TAGS_MAP_Comp_H
