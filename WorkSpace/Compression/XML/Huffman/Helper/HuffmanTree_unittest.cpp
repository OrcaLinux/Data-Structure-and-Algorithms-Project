/*****************************************************************//**
 * @file   HuffmanTree_unittest.cpp
 * @brief  A quick unit test for the HuffmanTree using gtest framework.
 *
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#include "pch.h"
#include "gtest/gtest.h"
#include "HuffmanTree.h"

namespace {
	class HuffmanTreeTest : public ::testing::Test {
	protected:
		// Set up the test fixture
		void SetUp() override {
			// Create a test string
			testString = "This is a test string for Huffman Tree implementation.";
			// Create a HuffmanTree object from the test string
			tree = HuffmanTree::generateTreeFromText(testString);
		}

		// Tear down the test fixture
		void TearDown() override {
			delete tree;
			tree = nullptr;
		}

		// Variables for testing
		HuffmanTree* tree;
		std::string testString;
	};

	// Test case for checking generation of Huffman Tree from text
	TEST_F(HuffmanTreeTest, GenerateTreeFromText) {
		// Check if tree is not null
		EXPECT_NE(tree, nullptr);
	}

	// Test case for checking encoding retrieval for a character
	TEST_F(HuffmanTreeTest, GetEncodingFromChar) {
		char testChar = 's'; // Character to test encoding
		std::vector<bool> encoding = tree->getEncodingFromChar(testChar);
		// Check if encoding is not empty
		EXPECT_FALSE(encoding.empty());
	}

	// Test case for checking decoding of character from encoding
	TEST_F(HuffmanTreeTest, GetCharFromEncoding) {
		char testChar = ' '; // Character to test decoding
		std::vector<bool> encoding = tree->getEncodingFromChar(testChar);
		char decodedChar = tree->getCharFromEncoding(encoding);
		// Check if decoded character matches the original character
		EXPECT_EQ(decodedChar, testChar);
	}

	// Test case for checking rebuilding tree from encoded string
	TEST_F(HuffmanTreeTest, RebuildTreeFromEncodedString) {
		std::string encodedTree = tree->getEncodedTree();
		int endPos = encodedTree.find(")\n"); // Find the end of the encoded tree
		encodedTree = encodedTree.substr(1, endPos - 1); // Exclude the ")\n" at the end

		HuffmanTree* rebuiltTree = HuffmanTree::rebuildTree(encodedTree);
		// Check if rebuilt tree is not null
		EXPECT_NE(rebuiltTree, nullptr);
		delete rebuiltTree;
		rebuiltTree = nullptr;
	}
}// namespace