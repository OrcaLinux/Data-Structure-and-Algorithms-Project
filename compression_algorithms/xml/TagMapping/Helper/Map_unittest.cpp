/*****************************************************************//**
 * @file   Map_unittest.cpp
 * @brief  Unit test code for Map class.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#include "gtest/gtest.h"
#include "pch.h"
#include "Map.h"

namespace {
	class Map_Test : public ::testing::Test {
	public:
		Map* m;
		std::string* s0;
		std::string* s1;
		std::string* s2;
		std::string* s3;

	protected:
		void SetUp() override {
			m = new Map();
			s0 = new std::string("v0");
			s1 = new std::string("v1");
			s2 = new std::string("v2");
			s3 = new std::string("v3");
		}

		void add() {
			m->add(s0);
			m->add(s1);
			m->add(s2);
			m->add(s3);
		}
		void TearDown() override {
			delete m;
			m = nullptr;
		}
	};

	TEST_F(Map_Test, emptyMap) {
		EXPECT_EQ(m->getSize(), 0);
		std::string* s = new std::string("any");
		EXPECT_EQ(m->getValue(s), -1);

		EXPECT_THROW(m->getKey(0), std::runtime_error);
		EXPECT_THROW(m->getKey(-1), std::runtime_error);
		EXPECT_THROW(m->getKey(5), std::runtime_error);

		EXPECT_FALSE(m->containKey(s));

		EXPECT_THROW(m->toString(), std::runtime_error);

		delete s;
		s = nullptr;
	}

	TEST_F(Map_Test, AddToTheMap) {
		add();

		EXPECT_EQ(m->getSize(), 4);

		EXPECT_EQ(m->getValue(s0), 0);
		EXPECT_EQ(m->getValue(s1), 1);
		EXPECT_EQ(m->getValue(s2), 2);
		EXPECT_EQ(m->getValue(s3), 3);

		EXPECT_THROW(m->getKey(5), std::runtime_error);

		EXPECT_EQ(m->getKey(0), s0);
		EXPECT_EQ(m->getKey(1), s1);
		EXPECT_EQ(m->getKey(2), s2);
		EXPECT_EQ(m->getKey(3), s3);

		EXPECT_TRUE(m->containKey(s0));
		EXPECT_TRUE(m->containKey(s1));
		EXPECT_TRUE(m->containKey(s2));
		EXPECT_TRUE(m->containKey(s3));

		std::string eOutput = "<TagMap>v0,v1,v2,v3</TagMap>";
		std::string* output = m->toString();
		EXPECT_EQ(*output, eOutput);
		delete output;
		output = nullptr;
	}

	class Map_Test2 : public::testing::Test {
	public:
		Map* m;
		std::string* TagMapBlock;
		std::string* output;
	protected:
		void SetUp() override {
			TagMapBlock = new std::string(R"(     <TagMap>   v0,v1,
       v2,   v3
       </TagMap>
       )");
			output = new std::string(R"(<TagMap>v0,v1,v2,v3</TagMap>)");
			m = new Map(TagMapBlock);
		}
		void TearDown() override {
			delete m;
			m = nullptr;
			delete TagMapBlock;
			TagMapBlock = nullptr;
			delete output;
			output = nullptr;
		}
	}; // Map_Test2

	TEST_F(Map_Test2, MapInitConstrucotr) {
		EXPECT_EQ(m->getSize(), 4);
		EXPECT_EQ(*m->getKey(0), "v0");
		EXPECT_EQ(*m->getKey(1), "v1");
		EXPECT_EQ(*m->getKey(2), "v2");
		EXPECT_EQ(*m->getKey(3), "v3");
		std::string* s = m->toString();
		EXPECT_EQ(*s, *output);
		delete s;
		s = nullptr;
	}
} // namespace