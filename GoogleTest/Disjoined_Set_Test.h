#pragma once
#include <gtest/gtest.h>
#include"../DataStructure/Disjoined_Set.h"

TEST(Disjoined_Set_Test, Basic_Test) {
	using namespace CLRS::DataStructure;
	typedef CLRS::DataStructure::Disjoined_Set_Node<int> Node_Type;

	std::shared_ptr<Node_Type> p1 = std::make_shared<Node_Type>(1);
	std::shared_ptr<Node_Type> p2 = std::make_shared<Node_Type>(2);
	std::shared_ptr<Node_Type> p3 = std::make_shared<Node_Type>(3);

	CLRS::DataStructure::Make_Set(p1);
	CLRS::DataStructure::Make_Set(p2);
	CLRS::DataStructure::Make_Set(p3);

	EXPECT_FALSE(Find_Set(p1) == Find_Set(p2));
	Union(p1, p2);
	EXPECT_TRUE(Find_Set(p1) == Find_Set(p2));
}