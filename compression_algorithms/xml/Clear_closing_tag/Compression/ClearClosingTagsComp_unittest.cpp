/*****************************************************************//**
 * @file   ClearClosingTagsComp_unittest.cpp
 * @brief  Unit test code for ClearClosingTagsComp class.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "gtest/gtest.h"
#include "ClearClosingTagsComp.h"

namespace {
	class ClearClosingTagsCompTest : public::testing::Test {
	public:
		ClearClosingTagsComp* c;
		std::string* input;
		std::string* output;
	protected:
		void SetUp() override {
			input = new std::string(R"(<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit ametffsjkn &alt; </body><topics><topic>economy</topic></topics></post></posts><followers><follower><id>2</id></follower></followers></user></users>)");

			output = new std::string(R"(<users><user><id>1<name>Ahmed Ali<posts><post><body>Lorem ipsum dolor sit ametffsjkn &alt; <topics><topic>economy<followers><follower><id>2)");

			c = new ClearClosingTagsComp(input);
		}

		void TearDown() override {
			delete c;
			c = nullptr;
			delete input;
			input = nullptr;
			delete output;
			output = nullptr;
		}
	};

	TEST_F(ClearClosingTagsCompTest, compressTest) {
		std::string* s = c->compress();
		EXPECT_EQ(*s, *output);

		delete s;
		s = nullptr;
	}
}// namespace