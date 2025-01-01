/*****************************************************************//**
 * @file   Tree.cpp
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

#include "Tree.h"

void Tree::printTreeNode(const TreeNode* node, int depth) const
{
	if (node == nullptr) {
		return;
	}

	for (int i = 0; i < depth; ++i) {
		std::cout << "  ";
	}

	std::cout << "|-- " << *node->value << std::endl;

	for (const TreeNode* child : *node->children) {
		printTreeNode(child, depth + 1);
	}
}

Tree::Tree() {
	// Creating nodes for the social network system tags
	root = new TreeNode(nullptr, new std::vector<TreeNode*>(), new std::string("users"));

	// Add child nodes for 'users'
	root->children->push_back(
		new TreeNode(root, new std::vector<TreeNode*>(), new std::string("user"))
	);

	// Add child nodes for 'user'
	(*root->children)[0]->children->push_back(
		new TreeNode((*root->children)[0], new std::vector<TreeNode*>(), new std::string("id"))
	);
	(*root->children)[0]->children->push_back(
		new TreeNode((*root->children)[0], new std::vector<TreeNode*>(), new std::string("name"))
	);
	(*root->children)[0]->children->push_back(
		new TreeNode((*root->children)[0], new std::vector<TreeNode*>(), new std::string("posts"))
	);
	(*root->children)[0]->children->push_back(
		new TreeNode((*root->children)[0], new std::vector<TreeNode*>(), new std::string("followers"))
	);

	// Add child nodes for 'posts'
	(*(*root->children)[0]->children)[2]->children->push_back(
		new TreeNode((*(*root->children)[0]->children)[2], new std::vector<TreeNode*>(), new std::string("post"))
	);

	// Add child nodes for 'post'
	(*(*(*root->children)[0]->children)[2]->children)[0]->children->push_back(
		new TreeNode((*(*(*root->children)[0]->children)[2]->children)[0], new std::vector<TreeNode*>(), new std::string("body"))
	);

	(*(*(*root->children)[0]->children)[2]->children)[0]->children->push_back(
		new TreeNode((*(*(*root->children)[0]->children)[2]->children)[0], new std::vector<TreeNode*>(), new std::string("topics"))
	);

	// Add child nodes for 'topics'
	(*(*(*(*root->children)[0]->children)[2]->children)[0]->children)[1]->children->push_back(
		new TreeNode((*(*(*(*root->children)[0]->children)[2]->children)[0]->children)[1], new std::vector<TreeNode*>(), new std::string("topic"))
	);

	// Add child nodes for 'followers'
	(*(*root->children)[0]->children)[3]->children->push_back(
		new TreeNode((*(*root->children)[0]->children)[3], new std::vector<TreeNode*>(), new std::string("follower"))
	);

	// Add child nodes for 'follower'
	(*(*(*root->children)[0]->children)[3]->children)[0]->children->push_back(
		new TreeNode((*(*(*root->children)[0]->children)[3]->children)[0], new std::vector<TreeNode*>(), new std::string("id"))
	);
}