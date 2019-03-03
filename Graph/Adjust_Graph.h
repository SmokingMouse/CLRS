#ifndef ADJUST_GRAPH_H
#define ADJUST_GRAPH_H

#include<array>
#include<map>
#include<vector>

namespace CLRS {
	namespace Graph{
		using std::array;
		using std::pair;
		using std::vector;
		using std::tuple;

		template<unsigned int N>
		class AdjGraph {
		public:
			typedef int VertexId;
			typedef int EdgeWeight;
			typedef tuple<VertexId, VertexId, EdgeWeight> EdgeType;
			typedef pair<VertexId, EdgeWeight> OutEdge;

			AdjGraph(){}

			void addEdge(VertexId from, VertexId to, EdgeWeight weight) {
				if (from < 0 || to < 0 || from >= N || to >= N) throw std::out_of_range("VertexId is out of range.");
				for (OutEdge& edge : adj_list_[from]) {
					if (edge.first == to) {
						edge.second = weight;
						return;
					}
				}
				adj_list_[from].push_back(std::make_pair(to, weight));
			}

			template<typename Iterator> void addEdges(const Iterator&, const Iterator&) {
				for (auto iter = begin; iter != end; ++iter) {
					addEdge(get<0>(*iter), get<1>(*iter), get<2>(*iter));
				}
			}

			const vector<OutEdge>& out_edge_of_vertex(VertexId v_id) const{
				if (v_id < 0 || v_id >= N) throw std::out_of_range("VertexId is out of range.");
				return adj_list_[v_id];
			}

			vector<EdgeType> EdgeTuples() const{
				vector<EdgeType> tuples;
				for (VertexId idx = 0; idx < N; idx++) {
					for (auto adj_iter = adj_list_[idx].begin(); adj_iter != adj_list_[idx].end(); ++adj_iter) {
						tuples.push_back(std::make_tuple(idx, adj_iter->first, adj_iter->second));
					}
				}
				return tuples;
			}

			void adjustEdge(VertexId s, VertexId d, EdgeWeight w) {
				auto out_edges = adj_list_[s];
				for (auto iter = out_edges.begin(); iter != out_edges.end(); ++iter) {
					if (iter->first == d) {
						iter->second = w; return;
					}
				}
				throw std::invalid_argument("doesn't exist s to d.");
			}
		private:
			array<vector<OutEdge>, N> adj_list_;
		};
	}
}


#endif
