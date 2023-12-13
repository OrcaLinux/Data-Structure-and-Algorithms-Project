/*****************************************************************//**
 * @file   Tree.h
 * @brief  A simple Tree DS implementation.
 * 
 * This tree is for arranging social network system tags.
 * it will be in this order:
 * 
 * - users --children--> {user}
 * - user --> {id,name,posts,followers}
 * - posts --> {post}
 * - post --> {body, topics}
 * - topics --> {topic}
 * - followers --> {follower}
 * - follower --> {id}
 * - not mentioned: doesn't have a child.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#pragma once
#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <iostream>

class Tree
{
private: 
	TreeNode* root;
	//for debugging
	void printTreeNode(const TreeNode* node, int depth) const;
public:
	/**
	 * @brief Initialize the Tree in that arrange for social network system:
	 * - users --children--> {user}
	 * - user --> {id,name,posts,followers}
	 * - posts --> {post}
	 * - post --> {body, topics}
	 * - topics --> {topic}
	 * - followers --> {follower}
	 * - follower --> {id}
	 * - not mentioned: doesn't have a child.
	 */
	explicit Tree();
	/**
	 * @brief D'tor.
	 * 
	 */
	~Tree() {
		delete root;
	}

	//getter
	TreeNode* getRoot() { return root; }
	//for debugging
	void print() const {
		printTreeNode(root, 0);
	}
};

#endif // !TREE_H



