/*****************************************************************//**
 * @file   ClearClosingTagsDec_unittest.cpp
 * @brief  Unit test code for ClearClosingTagsDec class.
 * 
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "gtest/gtest.h"
#include "ClearClosingTagsDec.h"

namespace{
	class ClearClosingTagsDecTest : public::testing::Test {
	public:
		ClearClosingTagsDec* c;
		std::string* input;
		std::string* output;
	protected:
		void SetUp() override {
			output = new std::string(R"(<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit ametffsjkn &alt; </body><topics><topic>economy</topic></topics></post></posts><followers><follower><id>2</id></follower></followers></user></users>)");

			input = new std::string(R"(<users><user><id>1<name>Ahmed Ali<posts><post><body>Lorem ipsum dolor sit ametffsjkn &alt; <topics><topic>economy<followers><follower><id>2)");

			c = new ClearClosingTagsDec(input);
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

	TEST_F(ClearClosingTagsDecTest, compressTest) {
		std::string* s = c->decompress();
		EXPECT_EQ(*s, *output);

		delete s;
		s = nullptr;
	}

} // namespace
