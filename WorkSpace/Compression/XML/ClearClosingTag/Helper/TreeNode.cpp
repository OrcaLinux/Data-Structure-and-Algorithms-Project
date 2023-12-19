/*****************************************************************//**
 * @file   TreeNode.cpp
 * @brief   A simple Tree Node for the tree data structure.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "TreeNode.h"

const TreeNode* TreeNode::getChild(const std::string* value) const
{
	//loop for all the vector until finding the needed child with the needed value.
	for (TreeNode* child : *children) {
		if (*child->value == *value) {
			return child;
		}
	}
	//if not found.
	return nullptr;
}