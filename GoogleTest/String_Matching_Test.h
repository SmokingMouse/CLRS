#pragma once
#include"../StringMatching/KMP.h"
#include"../StringMatching/Regular_Matching.h"
#include<gtest/gtest.h>

namespace CLRS {
	namespace StringMatching {
		TEST(Regular_Matching_Test, Basic_Test) {
			auto result = Regular_Matching("helloworldhello", "hello");
			EXPECT_EQ(result[0], 0);
			EXPECT_EQ(result[1], 10);
		}

		TEST(KMP_Test, Basic_Test) {
			auto result = KMP("helloworldhello", "hello");
		}
	}
}