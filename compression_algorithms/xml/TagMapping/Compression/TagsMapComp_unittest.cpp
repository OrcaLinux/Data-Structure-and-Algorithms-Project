/*****************************************************************//**
 * @file   TagsMapComp_unittest.cpp
 * @brief  Unit test code for TagsMapComp class.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "gtest/gtest.h"
#include "pch.h"
#include "TagsMapComp.h"

namespace {
	class TagsMapCompTest : public::testing::Test {
	public:
		TagsMapComp* t;
		std::string* input;
		std::string* result;
		std::string* resultWithMap;
	protected:
		void SetUp() {
			input = new std::string(R"(      <users>
        <user>
                  <id>        1       </id>
            <name>  Ahmed  Ali  </name>
            <posts>
                <post>
                    <body>  Lorem ipsum dolor sit ametffsjkn</body>
                    <topics>
                        <topic>     economy</topic>
                    </topics>
                </post>
            </posts>
            <followers>
                <follower>
                    <id>2           </id>
                </follower>
            </followers>
        </user>
    </users>     )");

			t = new TagsMapComp(input);

			result = new std::string(R"(      <0>
        <1>
                  <2>        1       </2>
            <3>  Ahmed  Ali  </3>
            <4>
                <5>
                    <6>  Lorem ipsum dolor sit ametffsjkn</6>
                    <7>
                        <8>     economy</8>
                    </7>
                </5>
            </4>
            <9>
                <10>
                    <2>2           </2>
                </10>
            </9>
        </1>
    </0>     )");

			resultWithMap = new std::string(R"(<TagMap>users,user,id,name,posts,post,body,topics,topic,followers,follower</TagMap>      <0>
        <1>
                  <2>        1       </2>
            <3>  Ahmed  Ali  </3>
            <4>
                <5>
                    <6>  Lorem ipsum dolor sit ametffsjkn</6>
                    <7>
                        <8>     economy</8>
                    </7>
                </5>
            </4>
            <9>
                <10>
                    <2>2           </2>
                </10>
            </9>
        </1>
    </0>     )");
		}

		void TearDown() {
			delete t;
			delete input;
			delete result;
			delete resultWithMap;
			t = nullptr;
			input = nullptr;
			result = nullptr;
			resultWithMap = nullptr;
		}
	}; // TagsMapCompTest

	TEST_F(TagsMapCompTest, noMap) {
		std::string* s = t->compress(false);
		EXPECT_EQ(*s, *result);

		delete s;
		s = nullptr;
	}

	TEST_F(TagsMapCompTest, withMap) {
		std::string* s = t->compress(true);
		EXPECT_EQ(*s, *resultWithMap);

		delete s;
		s = nullptr;
	}
}