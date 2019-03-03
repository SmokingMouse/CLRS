#pragma once
#include<gtest/gtest.h>
#include"../Select/Randomized_Select.h"
#include"../Select/Good_Select.h"

namespace CLRS {
	namespace Select {
		std::vector<int> getTestData() {
			return { 3,2,1,6,3,6,4 };
		}

		TEST(Randomized_Select_Test, Basic_Test) {
			auto data = getTestData();

			auto iter_1 = Randomized_Select(data.begin(), data.end(), 0, std::less<int>());
			auto iter_2 = Randomized_Select(data.begin(), data.end(), 1, std::less<int>());
			auto iter_3 = Randomized_Select(data.begin(), data.end(), 6, std::less<int>());
		
			EXPECT_EQ(1, *iter_1);
			EXPECT_EQ(2, *iter_2);
			EXPECT_EQ(6, *iter_3);
		}

		TEST(Good_Test, Basic_Test) {
			auto data = getTestData();
			auto iter_1 = Good_Select(data.begin(), data.end(), 0, std::less<int>());
			auto iter_2 = Good_Select(data.begin(), data.end(), 1, std::less<int>());
			auto iter_3 = Good_Select(data.begin(), data.end(), 6, std::less<int>());

			EXPECT_EQ(1, *iter_1);
			EXPECT_EQ(2, *iter_2);
			EXPECT_EQ(6, *iter_3);
		}
	}
}