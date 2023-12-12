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

class TagsMapDec
{
private:
	const std::string* xmlFile;

	const static std::string* defaultTagMapBlock;

	//Map of tag values.
	Map* map;

	//helper methods
	void getMapTags();
	void getTagsMapBlock();
public:
	explicit TagsMapDec();
	~TagsMapDec();

	std::string* decompress();
};
#endif // !TAGS_MAP_DEC_H
