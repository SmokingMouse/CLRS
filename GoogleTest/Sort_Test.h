#pragma once
#include<gtest/gtest.h>
#include"../Sort/BubbleSort.h"
#include"../Sort/InsertSort.h"
#include"../Sort/HeapSort.h"
#include"../Sort/QuickSort.h"
#include"../Sort/CountingSort.h"
#include"../Sort/RadixSort.h"
#include"../Sort/MergeSort.h"
#include"../Sort/BucketSort.h"
#include<algorithm>
#include<vector>
#include<string>
#include<iostream>

namespace CLRS {
	namespace Sort {
		using std::vector;
		using std::string;

		vector<int> getIntVector() {
			return { 2,1,5,6,7 };
		}

		vector<string> getStringVector() {
			return { "hello","zhang","peng" };
		}

		TEST(BubbleSort_Test, Basic_Test) {
			vector<int> int_data{ 9,7,7,9,6,5,5 };
			vector<string> string_data = getStringVector();
			vector<int> null_data;
			BubbleSort(int_data.begin(), int_data.end(), std::less<int>());
			BubbleSort(string_data.begin(), string_data.end(), std::less<string>());
			BubbleSort(null_data.begin(), null_data.end(), std::less<int>());
			vector<int> int_data_comp{ 5,5,6,7,7,9,9};
			vector<string> string_data_comp{ "hello","peng","zhang" };
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(string_data, string_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(InsertSort_Test, Basic_Test) {
			vector<int> int_data = getIntVector();
			vector<string> string_data = getStringVector();
			vector<int> null_data;
			InsertSort(int_data.begin(), int_data.end(), std::less<int>());
			InsertSort(string_data.begin(), string_data.end(), std::less<string>());
			InsertSort(null_data.begin(), null_data.end(), std::less<int>());
			vector<int> int_data_comp{ 1,2,5,6,7 };
			vector<string> string_data_comp{ "hello","peng","zhang" };
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(string_data, string_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(HeapSort_Test, Basic_Test) {
			vector<int> int_data = getIntVector();
			vector<string> string_data = getStringVector();
			vector<int> null_data;
			HeapSort(int_data.begin(), int_data.end(), std::less<int>());
			HeapSort(string_data.begin(), string_data.end(), std::less<string>());
			HeapSort(null_data.begin(), null_data.end(), std::less<int>());
			vector<int> int_data_comp{ 1,2,5,6,7 };
			vector<string> string_data_comp{ "hello","peng","zhang" };
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(string_data, string_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(QuickSort_Test, Basic_Test) {
			vector<int> int_data = getIntVector();
			vector<string> string_data = getStringVector();
			vector<int> null_data;
			QuickSort(int_data.begin(), int_data.end(), std::less<int>());
			QuickSort(string_data.begin(), string_data.end(), std::less<string>());
			QuickSort(null_data.begin(), null_data.end(), std::less<int>());
			vector<int> int_data_comp{ 1,2,5,6,7 };
			vector<string> string_data_comp{ "hello","peng","zhang" };
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(string_data, string_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(CountingSort_Test, Basic_Test) {
			vector<int> int_data{2,2,3,4,5,1,3,2,1};
			vector<int> null_data;
			CountingSort(int_data.begin(), int_data.end(), 5);
			CountingSort(null_data.begin(), null_data.end(),0);
			vector<int> int_data_comp{ 1,1,2,2,2,3,3,4,5 };
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(RadixSort_Test, Basic_Test) {
			vector<int> int_data{ 329,457,657,839,436,720,355 };
			vector<int> null_data;
			RadixSort(int_data.begin(), int_data.end(), std::less<int>(),3);
			RadixSort(null_data.begin(), null_data.end(), std::less<int>(), 0);
			vector<int> int_data_comp{329,355,436,457,657,720,839};
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(MergeSort_Test, Basic_Test) {
			vector<int> int_data{ 9,7,7,9,6,5,5 };
			vector<string> string_data = getStringVector();
			vector<int> null_data;
			MergeSort(int_data.begin(), int_data.end(), std::less<int>());
			MergeSort(string_data.begin(), string_data.end(), std::less<string>());
			MergeSort(null_data.begin(), null_data.end(), std::less<int>());
			vector<int> int_data_comp{ 5,5,6,7,7,9,9 };
			vector<string> string_data_comp{ "hello","peng","zhang" };
			vector<int> null_data_comp;
			EXPECT_EQ(int_data, int_data_comp);
			EXPECT_EQ(string_data, string_data_comp);
			EXPECT_EQ(null_data, null_data_comp);
		}

		TEST(BucketSort_Test, Basic_Test) {
			vector<int> int_data{ 78,17,39,26,72,94,21,12,23,68 };
			BucketSort(int_data.begin(), int_data.end(), std::less<int>(),12);
			vector<int> int_data_comp{ 12,17,21,23,26,39,68,72,78,94 };
			EXPECT_EQ(int_data, int_data_comp);
		}
	}
}
