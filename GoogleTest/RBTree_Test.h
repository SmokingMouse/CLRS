#pragma once
#include"../DataStructure/RBTree.h"
#include<gtest/gtest.h>
#include<algorithm>
namespace CLRS {
	namespace DataStructure {
		TEST(RBTree_Test, Basic_Test) {
			RBTree<RBNode<int, std::less<int>>> tree;
			tree.Insert(1);
			tree.Insert(4);
			tree.Insert(3);
			tree.Insert(6);
			tree.Insert(9);
			tree.Insert(7);
			tree.Insert(2);
			tree.Insert(5);
			tree.Insert(8);

			tree.Delete(tree.Search(8));
		}
	}
}