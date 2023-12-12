/*****************************************************************//**
 * @file   TagMapDec_unittest.cpp
 * @brief  Unit test code for TagsMapDec class.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "gtest/gtest.h"
#include "pch.h"
#include "TagsMapDec.h"

namespace {
	class TagsMapDecTest : public::testing::Test {
	public:
		TagsMapDec* t;
		std::string* inputWithMap;
		std::string* inputWithOutMap;
		std::string* result;
	protected:
		void SetUp() override {
			inputWithMap = new std::string(R"(<TagMap>users,user,id,name,posts,post,body,topics,topic,followers,follower</TagMap>      <t0>
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

			inputWithOutMap = new std::string(R"(      <t0>
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

			result = new std::string(R"(      <users>
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
		}

		void TearDown() {
			delete t;
			t = nullptr;
			delete inputWithMap;
			inputWithMap = nullptr;
			delete inputWithOutMap;
			inputWithOutMap = nullptr;
			delete result;
			result = nullptr;
		}
	};

	TEST_F(TagsMapDecTest, withMap) {
		t = new TagsMapDec(inputWithMap);
		std::string* s = t->decompress();
		EXPECT_EQ(*s, *result);

		delete s;
		s = nullptr;
	}

	TEST_F(TagsMapDecTest, withOutMap) {
		t = new TagsMapDec(inputWithOutMap);
		std::string* s = t->decompress();
		EXPECT_EQ(*s, *result);

		delete s;
		s = nullptr;
	}
}