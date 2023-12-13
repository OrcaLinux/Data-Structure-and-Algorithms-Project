/*****************************************************************//**
 * @file   TreeNode.cpp
 * @brief  A simple Tree Node for the tree DS.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "TreeNode.h"

const TreeNode* TreeNode::getChild(const std::string* value) const
{
	for (TreeNode* child : *children) {
		if (*child->value == *value) {
			return child;
		}
	}
	return nullptr;
}