#pragma once
#include"../DataStructure/Chained_Hash_Table.h"
#include"../DataStructure/Open_Addressing_Hash_Table.h"
#include<gtest/gtest.h>
#include<functional>

namespace CLRS {
	namespace DataStructure {
		TEST(Chained_Hash_Table_Test, Basic_Test) {
			Chained_Hash_Table<int, std::function<size_t(int,size_t)>, 17> table(Int_Div_Hash);
			for (int i = 0; i < 10; i++) table.Insert(i);
//			for (int i = 0; i < 10; i++) EXPECT_TRUE(table.Search(i));
			table.Delete(2);
			EXPECT_FALSE(table.Search(2));
		}

		TEST(Open_Hash_Table_Test, Basic_Test) {
			auto func = Quadratic_Probing_Int<10>;
			Open_Addressing_Hash_Table<int, 10> table(func);
			for (int i = 0; i < 10; i++) table.Insert(i);
			table.Delete(1);
		}
	}
}