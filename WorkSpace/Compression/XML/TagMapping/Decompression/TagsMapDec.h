/*****************************************************************//**
 * @file   TagsMapDec.h
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
 * <t0><t1><t2></t2><t2></t2></t1></t0>
 *
 * -> File after:
 * <tag0><tag1><tag2></tag2><tag2></tag2></tag1></tag0>
 *
 * @see TagsMapComp
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef TAGS_MAP_DEC_H
#define TAGS_MAP_DEC_H

#include "Map.h"
#include "MinifyingXML.h"
#include <string>

class TagsMapDec
{
private:
	const std::string* xmlFile;

	const static std::string* defualtTagMapBlock;

	//Map of tag values.
	Map* map;

	//helper methods

	/**
	 * @brief Initialize the map with mapping way in the XML file.
	 */
	void getMapTags();
	/**
	 * @brief Locates the <TagMap> block for mapping values..
	 *
	 * Operation:
	 * -Minify the file.
	 * -Get a sub str from the start to the closing tag of the block.
	 * -Return that sub string.
	 * -If the closing tag not available, return the default TagMap block.
	 * @return the TagMap line with the opening and closing tags.
	 *
	 * @throw runtime error for a defected file (the TagMap block is not in
	 * the begging of the file.)
	 */
	const std::string* getTagsMapBlock();
public:
	/**
	 * @brief C'tor.
	 * -Initialize the Map with the TagMap block.
	 *
	 * @param the XML file without the XML version and encoding line.
	 */
	explicit TagsMapDec(const std::string* xmlFile) : xmlFile(xmlFile) {
		getMapTags();
	}
	/**
	 * @brief D'tor.
	 *
	 */
	~TagsMapDec() {
		delete map;
		map = nullptr;
	}
	/**
	 * @brief This method decompresses the XML file.
	 *
	 * @see TagMapComp::compress() for the functionality.
	 * @return the file data after decompression.
	 */
	std::string* decompress();
};
#endif // !TAGS_MAP_DEC_H
