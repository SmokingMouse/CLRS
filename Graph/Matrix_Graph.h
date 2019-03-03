#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include<array>
#include<tuple>
#include<limits>
namespace CLRS {
	namespace Graph {
		extern const int MAX;

		template<unsigned int N>
		class MatrixGraph {
		public:
			typedef int VertexId;
			typedef int EdgeWeight;
			typedef std::tuple<VertexId, VertexId, EdgeWeight> EdgeType;
			typedef std::array<std::array<EdgeWeight, N>, N> MatrixType;

			MatrixGraph(){
				for (auto i = 0; i < N; i++) {
					for (auto j = 0; j < N; j++) {
						matrix_[i][j] = MAX;
					}
				}
			}
			void addEdge(VertexId from, VertexId to, EdgeWeight);
			template<typename Iterator> void addEdges(const Iterator&, const Iterator&);
			void adjustEdge(VertexId s, VertexId d, EdgeWeight w) {
				if (matrix_[s][d] == MAX) throw std::invalid_argument("doesn't exist s to d.");
				matrix_[s][d] = w;
			}
//		private:
			std::array<std::array<EdgeWeight, N>,N > matrix_;
		};
		template<unsigned int N>
		void MatrixGraph<N>::addEdge(VertexId from, VertexId to, EdgeWeight weight)
		{
			if (from < 0 || to < 0 || from >= N || to >= N) throw std::out_of_range("VertexId is out of range.");
			matrix_[from][to] = weight;
		}
		template<unsigned int N>
		template<typename Iterator>
		void MatrixGraph<N>::addEdges(const Iterator& begin, const Iterator& end)
		{
			for (auto iter = begin; iter != end; ++iter) {
				addEdge(get<0>(*iter), get<1>(*iter), get<2>(*iter));
			}
		}
	}
}



#endif