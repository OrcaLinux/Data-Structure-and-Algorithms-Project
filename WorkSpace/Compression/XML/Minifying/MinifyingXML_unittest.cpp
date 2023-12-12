/*****************************************************************//**
 * @file   MinifyingXML_unittest.cpp
 * @brief  Unit test code for MinifyingXML class.
 *
 * It includes a test for each member method in the class using gtest framework.
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/
#include "gtest/gtest.h"
#include "pch.h"
#include "MinifyingXML.h"

namespace {
	class MinifyingXML_Test_essintials : public ::testing::Test {
	protected:

		MinifyingXML* m;

		void SetUp() override {
			m = nullptr;  // Initialize m to nullptr in SetUp
			init_m(new std::string(""));
		}

		void TearDown()override { clearVar(); }

	public:
		// methods to help with C'tor tests.
		void clearVar() {
			delete m;  // Safe delete, checks if m is nullptr before deletion
			m = nullptr;  // Reset m to nullptr after deletion
		}
		void init_m(const std::string* s) {
			clearVar();
			m = new MinifyingXML(s);
		}
	}; // class MinifyingXML_Test_essintials

	//Getters and C'tor tests.
	TEST_F(MinifyingXML_Test_essintials, ConstructorAndGettersTest) {
		EXPECT_EQ(*m->getXMLFile(), "");

		// Test handling null pointer in initialization
		std::string* s = nullptr;
		EXPECT_THROW(init_m(s), std::logic_error);

		// Initialize with a valid string and verify the state
		s = new std::string("this is a new string.");
		init_m(s);
		EXPECT_EQ(*m->getXMLFile(), "this is a new string.");
		// Clean up memory after testing
		delete s;
		s = nullptr;
	}

	//Setters Test
	TEST_F(MinifyingXML_Test_essintials, SettersTest) {
		std::string* s = nullptr;
		EXPECT_THROW(m->setXMLFile(s), std::logic_error);

		//empty string
		s = new std::string("");
		m->setXMLFile(s);
		EXPECT_EQ(*m->getXMLFile(), "");

		delete s;
		s = nullptr;

		// any string
		s = new std::string("this is a new string.");
		m->setXMLFile(s);
		EXPECT_EQ(*m->getXMLFile(), "this is a new string.");

		delete s;
		s = nullptr;
	}

	//isChar test
	TEST_F(MinifyingXML_Test_essintials, isSkipCharTest) {
		//true cases.
		EXPECT_TRUE(MinifyingXML::isSkipChar(' '));
		EXPECT_TRUE(MinifyingXML::isSkipChar('\t'));
		EXPECT_TRUE(MinifyingXML::isSkipChar('\v'));
		EXPECT_TRUE(MinifyingXML::isSkipChar('\n'));
		EXPECT_TRUE(MinifyingXML::isSkipChar('\f'));

		//some false cases
		EXPECT_FALSE(MinifyingXML::isSkipChar('p'));
		EXPECT_FALSE(MinifyingXML::isSkipChar('a'));
		EXPECT_FALSE(MinifyingXML::isSkipChar('0'));
		EXPECT_FALSE(MinifyingXML::isSkipChar('3'));
		EXPECT_FALSE(MinifyingXML::isSkipChar('8'));
	}

	class MinifyingXML_Test_Functionality : public ::testing::Test {
	protected:
		const std::string* input1;
		const std::string* expectedResult;
		const std::string* afterMinifying;
		MinifyingXML* m;
		void SetUp() override {
			input1 = new std::string(R"(      <users>
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

			expectedResult = new std::string(R"(<users><user><id>1       </id><name>Ahmed  Ali  </name><posts><post><body>Lorem ipsum dolor sit ametffsjkn</body><topics><topic>economy</topic></topics></post></posts><followers><follower><id>2           </id></follower></followers></user></users>)");

			afterMinifying = new std::string(R"(<users><user><id>1</id><name>Ahmed  Ali</name><posts><post><body>Lorem ipsum dolor sit ametffsjkn</body><topics><topic>economy</topic></topics></post></posts><followers><follower><id>2</id></follower></followers></user></users>)");

			m = new MinifyingXML(input1);
		}

		void TearDown() override {
			delete input1;
			delete expectedResult;
			delete afterMinifying;

			input1 = nullptr;
			expectedResult = nullptr;
			afterMinifying = nullptr;
		}
	}; // class MinifyingXML_Test_Functionality

	//helper functions test
	TEST_F(MinifyingXML_Test_Functionality, skipFromBeginningTest) {
		//action
		std::string* output = new std::string();
		m->skipFromBeginning(output);

		//test
		EXPECT_EQ(*output, *expectedResult);

		//deallocate
		delete output;
		output = nullptr;
	}

	TEST_F(MinifyingXML_Test_Functionality, skipFromEndTest) {
		//action
		std::string* output = new std::string(*expectedResult);
		m->skipFromEnd(output);

		//test
		EXPECT_EQ(*output, *afterMinifying);

		//deallocate
		delete output;
		output = nullptr;
	}

	TEST_F(MinifyingXML_Test_Functionality, minifyStringTest) {
		//action
		const std::string* output = m->minifyString();

		//test
		EXPECT_EQ(*output, *afterMinifying);

		//deallocate
		delete output;
		output = nullptr;
	}
} // namespace