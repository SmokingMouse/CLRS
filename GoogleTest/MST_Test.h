#pragma once
#include<gtest/gtest.h>
#include"../Graph/Graph.h"
#include"../Graph/Minimum_Spanning_Tree.h"
#include"../Graph//Vertex.h"
#include"../DataStructure/Heap.h"


namespace CLRS {
	namespace Graph {
		Graph<Path_Vertex<int>, 9>* Product_Test_Graph() {
			using GraphType = Graph<Path_Vertex<int>, 9>;
			using EdgeTuple = GraphType::EdgeType;

			GraphType* ptr = new GraphType();
			for (int i = 0; i < 9; i++)
				ptr->addVertex(0);
			vector<EdgeTuple> edges{ {0,1,4},{0,7,8},{1,7,11},{1,2,8},{2,3,7},{2,5,4},
				{2,8,2},{3,4,9},{3,5,14},{4,5,10},{5,6,2},{6,7,1},{6,8,6},{7,8,7},
			{ 1,0,4 },{ 7,0,8 },{ 7,1,11 },{ 2,1,8 },{ 3,2,7 },{ 5,2,4 },
			{ 8,2,2 },{ 4,3,9 },{ 5,3,14 },{ 5,4,10 },{ 6,5,2 },{ 7,6,1 },{ 8,6,6 },{ 8,7,7 } };
			ptr->addEdges(edges.begin(), edges.end());
			return ptr;
		}

		TEST(Kruskal_Test, Basic_Test) {
			auto graph_ptr = Product_Test_Graph();
			auto result = Kruskal(graph_ptr);
			delete graph_ptr;
			EXPECT_EQ(result.size(), 8);
			EXPECT_EQ(std::get<2>(result[0]), 1);
			EXPECT_EQ(std::get<2>(result[1]), 2);
			EXPECT_EQ(std::get<2>(result[2]), 2);
			EXPECT_EQ(std::get<2>(result[3]), 4);
			EXPECT_EQ(std::get<2>(result[4]), 4);
			EXPECT_EQ(std::get<2>(result[5]), 7);
			EXPECT_EQ(std::get<2>(result[6]), 8);
			EXPECT_EQ(std::get<2>(result[7]), 9);
		}

		TEST(Prim_Test, Basic_Test) {
			auto graph_ptr = Product_Test_Graph();
			using GraphType = Graph<Path_Vertex<int>, 9>;
			using Heap = CLRS::DataStructure::Heap<typename GraphType::VertexType*>;
			auto result = Prim<GraphType,Heap>(graph_ptr, 0);
		}
	}
}
