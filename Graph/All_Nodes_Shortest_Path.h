#pragma once

#include<array>
#include<map>
#include<memory>
#include<tuple>
#include"../DataStructure/Heap.h"
namespace CLRS {
	namespace Graph {
		using std::array;
		using std::pair;
		using std::shared_ptr;
		using std::get;
		extern const int MAX;

		/*
		Assume matrix[i][j] represents the path of i to j which the length is equal less than n-1, 
		and Extend_Shortest_Paths gives the path of i to j which the length is equal less than n;
		Complexity O(V^3).
		*/
		template<class MatrixType>
		MatrixType Extend_Shortest_Paths(const MatrixType& matrix, const MatrixType& edges) {
			MatrixType result = matrix;

			int size = result.size();
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					for (int k = 0; k < size; k++) {
						result[i][j] = std::min(result[i][j],(matrix[i][k] == MAX || edges[k][j] == MAX) ? MAX : matrix[i][k] + edges[k][j]);
					}
				}
			}
			return result;
		}

		/*
		for the shortest path is simple path. The length of path is equal less than n - 1;
		Complexity O(V^4)
		*/
		template<class GraphType>
		typename GraphType::MatrixType Slow_All_Pairs_Shortest_Paths(const GraphType* graph) {
			typedef typename GraphType::MatrixType MatrixType;
			
			MatrixType path;
			int row_num = path.size();
			int col_num = row_num;
			for (int i = 0; i < row_num; i++)
				for (int j = 0; j < col_num; j++) {
					path[i][j] = (i == j ? 0 : graph->matrix_graph_.matrix_[i][j]);
				}

			int vertexNum = row_num;
			MatrixType shortest_path = path;
			for (int cnt = 2; cnt < vertexNum; cnt++) {
				shortest_path = Extend_Shortest_Paths(shortest_path, path);
			}

			return shortest_path;
		}

		/*
		a faster algorithm.
		Complexity O(V^3 * log(V))
		*/
		template<class GraphType>
		typename GraphType::MatrixType Fast_All_Pairs_Shortest_Paths(const GraphType* graph) {
			typedef typename GraphType::MatrixType MatrixType;

			MatrixType path;
			int row_num = path.size();
			int col_num = row_num;
			for (int i = 0; i < row_num; i++) {
				for (int j = 0; j < col_num; j++) {
					path[i][j] = (i == j ? 0 : graph->matrix_graph_.matrix_[i][j]);
				}
			}

			int m = 1;
			while (m < row_num - 1) {
				path = Extend_Shortest_Paths(path, path);
				m *= 2;
			}

			return path;
		}

		/*
		Walshall Algorithm.
		Complexity O(V^3).
		*/

		template<class GraphType>
		pair<array<array<typename GraphType::EdgeWeight,GraphType::NUM>,GraphType::NUM>,
			array<array<typename GraphType::VertexId,GraphType::NUM>,GraphType::NUM>>
			Floyd_Walshall(const GraphType* graph) {
			typedef typename GraphType::MatrixType MatrixType;
			typedef typename GraphType::VertexId VertexId;
			const int vertexCnt = GraphType::NUM;

			MatrixType path;
			array<array<VertexId, vertexCnt>, vertexCnt> pai;

			int row_num = vertexCnt;
			int col_num = vertexCnt;
			for (int i = 0; i < row_num; i++) {
				for (int j = 0; j < col_num; j++) {
					path[i][j] = (i == j ? 0 : graph->matrix_graph_.matrix_[i][j]);
					pai[i][j] = path[i][j] == MAX || i == j ? -1 : i;
				}
			}

			int m = 0;
			while (m < vertexCnt) {
				for (int i = 0; i < row_num; i++) {
					for (int j = 0; j < col_num; j++) {
						if (path[i][j] > path[i][m] + path[m][j]) { 
							//here, must be > rathan then >=, which may make m as the parent of m.
							path[i][j] = path[i][m] + path[m][j];
							pai[i][j] = pai[m][j];
						}
						
						path[i][j] = std::min(path[i][j], path[i][m] + path[m][j]);
					}
				}
				m++;
			}

			return std::make_pair(path, pai);
		}

		template<class GraphType>
		Graph<typename GraphType::VertexType, GraphType::NUM + 1>* build_new_graph(const GraphType* graph) {
			typedef Graph<typename GraphType::VertexType, GraphType::NUM + 1> NewGraphType;
			typedef typename NewGraphType::VertexType VertexType;

			const int vertexCnt = GraphType::NUM;

			NewGraphType* result = new NewGraphType();
			for (int i = 0; i < vertexCnt; i++) {
				auto vertex = graph->vertexes_[i];
				if (vertex)
					result->addVertex(vertex->key_, vertex->id_);
			}
			result->addVertex(0, vertexCnt);

			auto edges = graph->EdgeTuples();
			result->addEdges(edges.begin(), edges.end());
			for (int i = 0; i < vertexCnt; i++) {
				result->addEdge({ vertexCnt,i,0 });
			}

			return result;
		}

		template<class GraphType>
		array<array<typename GraphType::EdgeWeight,GraphType::NUM>,GraphType::NUM>
			Johnson(const GraphType* graph) {
			const int vertexCnt = GraphType::NUM;

			typedef typename GraphType::VertexId VertexId;
			typedef typename GraphType::EdgeWeight EdgeWeight;
			typedef Graph<typename GraphType::VertexType, vertexCnt + 1> NewGraphType;
			
			Graph<typename GraphType::VertexType,vertexCnt+1>* new_graph = build_new_graph(graph);

			if (!Bellman_Ford(new_graph, vertexCnt)) throw std::invalid_argument("the graph has negative loop.");

			int H[vertexCnt];
			for (int i = 0; i < vertexCnt; i++) {
				H[i] = new_graph->vertexes_[i]->distance_;
			}

			auto edges = new_graph->EdgeTuples();
			for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
				VertexId s = get<0>(*iter);
				VertexId d = get<1>(*iter);
				EdgeWeight w = get<2>(*iter);
				new_graph->adjustEdge(s, d, w + H[s] - H[d]);
			}
			
			array<array<EdgeWeight, vertexCnt>, vertexCnt> result;

			for (int i = 0; i < vertexCnt; i++) {
				Dijkstra<NewGraphType, CLRS::DataStructure::Heap<typename NewGraphType::VertexPtr>>(new_graph, i);
				for (int j = 0; j < vertexCnt; j++) {
					EdgeWeight distance = new_graph->vertexes_[j]->distance_;
					result[i][j] = (distance == MAX ? MAX : distance + H[j] - H[i]);
				}
			}
			delete new_graph;
			return result;
		}
	}
}