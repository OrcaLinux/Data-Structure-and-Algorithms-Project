/*****************************************************************//**
 * @file   TreeNode.h
 * @brief  A simple Tree Node for the tree DS.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#pragma once
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>
#include <vector>
class TreeNode
{
	friend class Tree;
private:
	const TreeNode* parentNode;
	std::vector<TreeNode*>* children;
	std::string* value;

public:
	explicit TreeNode(const TreeNode* parentNode, std::vector<TreeNode*>* children, std::string* value)
		: parentNode(parentNode), children(children) , value(value) {}

	~TreeNode() {
		for (TreeNode* child : *children) {
			delete child;
		}
		delete children;
		delete value;
	}

	//methods.
	/**
	 * @brief Returns The child with the assigned value.
	 * 
	 * @param value
	 * @return child TreeNode
	 */
	const TreeNode* getChild(const std::string* value) const;
	/**
	 * @brief Returns the parent of this node.
	 */
	const TreeNode* getParent()const { return this->parentNode; }
	/**
	 * @brief check if the value is for a child or not.
	 * 
	 * @param value
	 * @return true if found, false otherwise.
	 */
	bool isChild(const std::string* value) const { return getChild(value) != nullptr;	}

	//getter
	std::string getValue() const { return *value; }

};
#endif // !TREE_NODE_H



