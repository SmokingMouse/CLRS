#pragma once

#include"../DataStructure/Disjoined_Set.h"
#include<algorithm>
#include<tuple>
#include<vector>
namespace CLRS {
	namespace Graph {
		template<class GraphType>
		std::vector<typename GraphType::EdgeType> Kruskal(GraphType* graph) {
			using std::shared_ptr;
			using std::make_shared;
			using std::vector;
			using CLRS::DataStructure::Make_Set;
			using CLRS::DataStructure::Find_Set;
			typedef typename GraphType::EdgeType EdgeType;
			typedef typename GraphType::EdgeWeight EdgeWeight;
			typedef typename GraphType::VertexId VertexId;
			typedef CLRS::DataStructure::Disjoined_Set_Node<VertexId> Set_Node;

			vector<shared_ptr<Set_Node>> set_nodes;
			vector<EdgeType> result;
			for (int i = 0; i < GraphType::NUM; i++) {
				set_nodes.push_back(make_shared<Set_Node>(i));
				Make_Set(set_nodes[i]);
			}
			auto edges = graph->EdgeTuples();
			std::sort(edges.begin(),edges.end(),
				[](const std::tuple<int,int,int>& l, const std::tuple<int,int,int>& r) {
				return std::get<2>(l) < std::get<2>(r);
			});
			for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
				auto l_ptr = Find_Set(set_nodes[std::get<0>(*iter)]);
				auto r_ptr = Find_Set(set_nodes[std::get<1>(*iter)]);
				
				if (l_ptr != r_ptr)
				{
					Union(l_ptr, r_ptr);
					result.push_back(*iter);
				}
			}
			return result;
		}

		template<class GraphType,class HeapType>
		std::vector<typename GraphType::EdgeType> Prim(GraphType* graph,typename GraphType::VertexId src){
			typedef typename GraphType::VertexType VertexType;
			typedef VertexType* VertexPtr;

			/*initialize all the nodes.*/
			std::vector<VertexPtr> vertexes;
			for (int i = 0; i < GraphType::NUM; i++) {
				vertexes.push_back(graph->vertexes_[i]);
			}
			for (auto elem : vertexes) {
				elem->p_ = NULL;
				elem->distance_ = MAX;
			}
			graph->vertexes_[src]->distance_ = 0;

			auto compare = 
				[](const VertexType* l, const VertexType* r) {
				return l->distance_ < r->distance_;
			};
			auto keyValue = [](VertexType* v)->int& {return v->distance_; };

			HeapType heap(vertexes, compare, keyValue);
			std::vector<typename GraphType::EdgeType> result;
			VertexPtr ptr;
			VertexPtr vertexPtr = NULL;
			auto search = [&vertexPtr](const VertexPtr& v) {return v == vertexPtr; };
			while (heap.heapSize() > 0) {
				ptr = heap.extract();
				if (ptr->id_ != src)
					result.push_back(std::make_tuple(ptr->p_->id_, ptr->id_, ptr->distance_));
				auto out_edges = graph->out_edge_of_vertex(ptr->id_);
				for (auto edge : out_edges) {
					vertexPtr = vertexes[edge.first];
					if (heap.search(vertexPtr)&&vertexPtr->distance_ > edge.second) {
						heap.increase(search, edge.second);
						vertexPtr->p_ = ptr;
					}
				}
			}
			return result;			
		}
	}
}
