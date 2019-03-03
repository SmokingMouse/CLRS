#pragma once

#include<stdexcept>
#include<limits>
#include<tuple>
#include<list>
#include<map>
namespace CLRS {
	namespace Graph {

		extern const int MAX;

		bool judge(int l,int inc, int r) {
			if (l == MAX) return false;
			if (r == MAX) return true;
			return l + inc < r;
		}

		template<class VertexType>
		void relax(VertexType* src, VertexType* des, int weight) {
			if (!src) throw std::invalid_argument("src Vertex ptr is NULL.");
			if (!des) throw std::invalid_argument("des vetex ptr is NULL.");

			if (src->distance_ == MAX) return;

			if (src->distance_ + weight < des->distance_) {
				des->distance_ = src->distance_ + weight;
				des->p_ = src;
			}
		}

		template<class GraphType>
		void initVertexes(const GraphType* graph) {
			for (auto item : graph->vertexes_) {
				if (item) {
					item->p_ = NULL;
					item->distance_ = MAX;
				}
			}
		}

		/*
		BellmanFord Algorithm. Suits any situations.
		Complexity O(E * (V - 1)).
		*/
		template<class GraphType>
		bool Bellman_Ford(const GraphType* graph, typename GraphType::VertexId src) {
			auto edges = graph->EdgeTuples();
			int vertexCnt = graph->countOfVertexes();
			
			initVertexes(graph);
			if (!graph->vertexes_[src]) throw std::invalid_argument("the src is not exsit.");
			graph->vertexes_[src]->p_ = NULL;
			graph->vertexes_[src]->distance_ = 0;

			for (int times = 1; times < vertexCnt; times++) {
				for (typename GraphType::EdgeType edge : edges) {
					relax(graph->vertexes_[std::get<0>(edge)], graph->vertexes_[std::get<1>(edge)], std::get<2>(edge));
				}
			}
			for (auto item : edges) {
				if (judge(graph->vertexes_[std::get<0>(item)]->distance_, std::get<2>(item), graph->vertexes_[std::get<1>(item)]->distance_))
					return false;
			}
			return true;
		}

		/*
		Dag_Shortest_Path, only suits graphs does't have loop.
		Complexity O(E + V).
		*/
		template<class GraphType>
		void Dag_Shortest_Path(const GraphType* graph,typename GraphType::VertexId src) {
			if (!graph->vertexes_[src]) throw std::invalid_argument("the src is not exsit.");
			std::list<typename GraphType::VertexId> topoRank = TopoSort(graph);
			initVertexes(graph);
			graph->vertexes_[src]->p_ = NULL;
			graph->vertexes_[src]->distance_ = 0;
			auto src_iter = std::find(topoRank.begin(), topoRank.end(), src);
			topoRank.erase(src_iter);
			topoRank.emplace_front(src);
			for (auto item : topoRank) {
				for (const auto& edge : graph->out_edge_of_vertex(item)) {
					relax(graph->vertexes_[item], graph->vertexes_[edge.first],edge.second);
				}
			}
		}


		/*
		Dijstra Algorithm, only suits the graph of which the edge is negtive.
		The complexity is O(V^2 + E).
		*/
		template<class GraphType,class Heap>
		bool Dijkstra(const GraphType* graph, typename GraphType::VertexId src) {
			typedef typename GraphType::VertexPtr VType;
			typedef typename GraphType::VertexType::Distance Key;
			typedef typename GraphType::VertexId VertexId;

			if (!graph->vertexes_[src]) throw std::invalid_argument("the src is not exsit.");


			initVertexes(graph);

			function<Key&(VType& v)> keyType = [](VType& v)->Key& {return v->distance_; };
			function<bool(const VType& l, const VType& r)> compare = [](const VType& l, const VType& r) { return l->distance_ < r->distance_; };
			
			Heap min_heap({},compare,keyType);
			for (auto item : graph->vertexes_) {
				if(item)
					min_heap.insert(item);
			}
			VType target = graph->vertexes_[src];
			VType edgeEnd = target;
			function<bool(const VType&)> search = [&edgeEnd](const VType& id) {return id->id_ == edgeEnd->id_; };
			min_heap.increase(search,  0);
			
			while (min_heap.heapSize() > 0) {
				target = min_heap.extract();
				int areaDistance = target->distance_;
				if (areaDistance != MAX) {
					for (auto edge : graph->out_edge_of_vertex(target->id_)) {
						if (areaDistance + edge.second < graph->vertexes_[edge.first]->distance_)
						{
							edgeEnd = graph->vertexes_[edge.first];
							min_heap.increase(search, areaDistance + edge.second);
							graph->vertexes_[edge.first]->p_ = target;
						}	
					}
				}
			}
			
		}
	}
}

