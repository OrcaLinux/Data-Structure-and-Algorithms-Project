/*****************************************************************//**
 * @file   TagsMapDec_unittest.cpp
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
			inputWithMap = new std::string(R"(<TagMap>users,user,id,name,posts,post,body,topics,topic,followers,follower</TagMap>      <0>
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

			inputWithOutMap = new std::string(R"(      <0>
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