/*****************************************************************//**
 * @file   Map.h
 * @brief  The header file of the simple Map.
 *
 * This a simple implementation of Map DS that will help Mapping
 * tags into numbers.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>
#include "MinifyingXML.h"
#include <sstream>

class Map
{
private:
	std::vector<std::string*>* arr;

	//helper method
	/**
	 * @brief Trim spaces from both ends of a string.
	 *
	 * @param str
	 */
	static void trimString(std::string& str);

public:
	/**
	 * @brief C'tor.
	 * Initializes empty map with an empty dynamic array.
	 */
	explicit Map() :arr(new std::vector<std::string*>()) {}
	/**
	 * @brief C'tor.
	 * Initialize the map from a <TagMap> block.
	 *
	 * The file must start with <TagMap> and ends with </TagMap>
	 * otherwise the file is considered defected.
	 * @param tagMapBlock.
	 * @throw runtime_error if the file is defected.
	 */
	explicit Map(const std::string* tagMapBlock);
	/**
	 * D'tor.
	 * @warning It will delete all the keys string assigned to it.
	 */
	~Map() {
		for (std::string* s : *arr) {
			delete s;
		}
		delete arr;
	}

	//methods

	/**
	 * @brief Adds the key to the map.
	 *
	 * @param key To add.
	 * @return The value that the key is mapped to.
	 */
	int add(std::string* key);
	/**
	 * @brief The value that the key is mapped to.
	 *
	 * @param key.
	 * @return The value if the key is found, -1 otherwise.
	 */
	int getValue(const std::string* key) const;
	/**
	 * @brief Get the key from the value that the key was mapped to.
	 *
	 * @param value
	 * @return The key.
	 * @throw runtime error if the value is not in the map.
	 */
	const std::string* getKey(int value) const;
	/**
	 * @brief Checks if the map contains that key.
	 *
	 * @param key.
	 * @return true if the key is available in the map,
	 * false otherwise.
	 */
	bool containKey(const std::string* key) const;

	/**
	 * @return the size of the map.
	 */
	int getSize() { return arr->size(); }

	/**
	 * @brief Returns the <TagMap> block so it can be added to the
	 * compressed XML file.
	 *
	 * @throw runtime error if the map is empty.
	 */
	std::string* toString();
};

#endif // !MAP_H
