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

			result = new std::string(R"(      <t0>
        <t1>
                  <t2>        1       </t2>
            <t3>  Ahmed  Ali  </t3>
            <t4>
                <t5>
                    <t6>  Lorem ipsum dolor sit ametffsjkn</t6>
                    <t7>
                        <t8>     economy</t8>
                    </t7>
                </t5>
            </t4>
            <t9>
                <t10>
                    <t2>2           </t2>
                </t10>
            </t9>
        </t1>
    </t0>     )");

			resultWithMap = new std::string(R"(<TagMap>users,user,id,name,posts,post,body,topics,topic,followers,follower</TagMap>      <t0>
        <t1>
                  <t2>        1       </t2>
            <t3>  Ahmed  Ali  </t3>
            <t4>
                <t5>
                    <t6>  Lorem ipsum dolor sit ametffsjkn</t6>
                    <t7>
                        <t8>     economy</t8>
                    </t7>
                </t5>
            </t4>
            <t9>
                <t10>
                    <t2>2           </t2>
                </t10>
            </t9>
        </t1>
    </t0>     )");
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