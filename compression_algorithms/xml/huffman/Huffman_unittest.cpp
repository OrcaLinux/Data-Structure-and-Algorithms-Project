/*****************************************************************//**
 * @file   Huffman_unittest.cpp
 * @brief
 *
 *
 * @author eslam
 * @date   December 2023
 *********************************************************************/

#include "pch.h"
#include "gtest/gtest.h"
#include "HuffmanComp.h"
#include "HuffmanDec.h"

namespace {
	TEST(HuffmanCompression, CompressionDecompression) {
		std::string* inputString = new std::string(R"(<t0><t1><t2>1<t3>Ahmed Ali<t4><t5><t6>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.<t7><t8>economy<t8>finance<t5><t6>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.<t7><t8>solar_energy<t9><t10><t2>2<t10><t2>3<t1><t2>2<t3>Yasser Ahmed<t4><t5><t6>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.<t7><t8>education<t9><t10><t2>1<t1><t2>3<t3>Mohamed Sherif<t4><t5><t6>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.<t7><t8>sports<t9><t10><t2>1)");

		// Compress the input string
		HuffmanComp* compressor = new HuffmanComp(inputString);
		std::string* compressedString = compressor->compress();

		// Decompress the compressed string
		HuffmanDec* decompressor = new HuffmanDec(compressedString);
		std::string* decompressedString = decompressor->decompress();

		// Check if the decompressed string matches the original input
		EXPECT_EQ(*decompressedString, *inputString);

		// Clean up memory
		delete compressor;
		delete decompressor;
		compressedString = nullptr;
		decompressedString = nullptr;
		compressor = nullptr;
		decompressor = nullptr;
	}
}