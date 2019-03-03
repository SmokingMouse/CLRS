#ifndef GRAPH_H
#define GRAPH_H

#include<tuple>
#include<vector>
#include<array>
#include<memory>
#include"Matrix_Graph.h"
#include"Adjust_Graph.h"

namespace CLRS{
	namespace Graph{
		using std::tuple;
		using std::vector;
		using std::array;
		using std::shared_ptr;
		using std::get;

		template<class VType,unsigned int N>
		class Graph {
		public:
			typedef int VertexId;
			typedef int EdgeWeight;
			typedef VType VertexType;
			typedef tuple<VertexId, VertexId, EdgeWeight> EdgeType;
			typedef VertexType* VertexPtr;
			typedef typename MatrixGraph<N>::MatrixType MatrixType;

			static const unsigned int NUM = N;

			Graph():next_empty_vertex_(0){
				for (auto& item : vertexes_) item = nullptr;
			}
			~Graph() {
				for (VertexPtr ptr : vertexes_) {
					delete ptr;
					ptr = NULL;
				}
			}
			Graph& operator=(const Graph& other) = delete;
			Graph(const Graph&) = delete;

			VertexId addVertex(const typename VType::KeyType& key) {
				while (next_empty_vertex_ < N && vertexes_[next_empty_vertex_]!=nullptr) next_empty_vertex_++;
				if (next_empty_vertex_ >= N) throw std::out_of_range("the graph is full of vertexed.");
				vertexes_[next_empty_vertex_] = new VertexType(key, next_empty_vertex_);
				return next_empty_vertex_;
			}

			VertexId addVertex(const typename VType::KeyType& key, VertexId id) {
				if (vertexes_[id]) throw std::invalid_argument("the id has vertex.");
				vertexes_[id] = new VertexType(key, id);
				return id;
			}

			const vector<typename AdjGraph<N>::OutEdge>& out_edge_of_vertex(VertexId v_id) const{
				return adj_graph_.out_edge_of_vertex(v_id);
			}

			void addEdge(const EdgeType& edge) {
				adj_graph_.addEdge(get<0>(edge), get<1>(edge), get<2>(edge));
				matrix_graph_.addEdge(get<0>(edge), get<1>(edge), get<2>(edge));
			}

			template<typename Iterator> 
			void addEdges(const Iterator& begin, const Iterator& end) {
				for (auto iter = begin; iter != end; ++iter) {
					addEdge(*iter);
				}
			}
			vector<EdgeType> EdgeTuples() const{
				return adj_graph_.EdgeTuples();
			}

			shared_ptr<Graph> inverse() const{
				shared_ptr<Graph> graph = std::make_shared<Graph>();
				for (VertexId id = 0; id < N; ++id) {
					if(vertexes_[id])
						graph->vertexes_[id] = new VertexType(vertexes_[id]->key_,id);
				}

				auto edge_tuples = EdgeTuples();
				for (tuple<int,int,int>& edge_tuple : edge_tuples) {
					std::swap(std::get<0>(edge_tuple), std::get<1>(edge_tuple));
				}

				graph->addEdges(edge_tuples.begin(),edge_tuples.end());
				return graph;
			}

			void adjustEdge(VertexId s, VertexId e, EdgeWeight w) {
				adj_graph_.adjustEdge(s, e, w);
				matrix_graph_.adjustEdge(s, e, w);
			}

			int countOfVertexes() const{
				int result = 0;
				for (auto item : vertexes_)
					result +=(item != NULL);
				return result;
			}



//		private:
			AdjGraph<N> adj_graph_;
			MatrixGraph<N> matrix_graph_;
			array<VertexPtr, N> vertexes_;
			int next_empty_vertex_;
		};
	}
	
}

#endif