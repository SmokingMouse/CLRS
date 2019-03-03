#ifndef BASIC_ALGORITHM_H
#define BASIC_ALGORITHM_H

#include<functional>
#include<stdexcept>
#include<queue>
#include<list>
#include<vector>
namespace CLRS {
	namespace Graph {
		using std::function;
		using std::queue;
		using std::list;
		using std::vector;

		template<class GraphType>
		void BFS(typename GraphType::VertexId srcV, const GraphType* graph)
		{
			typedef typename GraphType::VertexId VertexId;
			typedef typename GraphType::VertexType VertexType;

			if (!graph) throw std::invalid_argument("graph is empty");
			if (srcV < 0 || srcV >= GraphType::NUM || !graph->vertexes_.at(srcV))
				throw std::invalid_argument("the srcId is out of range.");
			for (auto vertex : graph->vertexes_) {
				if (!vertex) continue;
				vertex->color_ = VertexType::Color::White;
				vertex->p_ = NULL;
				vertex->distance_ = 0;
			}

			queue<VertexType*> v_queue;
			VertexType* src_v = graph->vertexes_[srcV];
			src_v->color_ = VertexType::Color::Gray;
			v_queue.push(src_v);
			while (!v_queue.empty()) {
				VertexType* v_front = v_queue.top();
				const auto& adj_lists = graph->out_edge_of_vertex(v_front->id_);
				v_queue.pop();
				for (auto i : adj_lists) {
					VertexId next_id = i.first;
					VertexType* next_vertex = graph->vertexes_.at(next_id);
					if (next_vertex->color_ != VertexType::Color::White) continue;
					next_vertex->set_found(v_front);
					v_queue.push(next_vertex);
				}
				v_front->color_ = VertexType::Color::Black;
			}
			
		}


		template<class GraphType>
		void visit(typename GraphType::VertexId srcV, const GraphType* graph, int& time, function<void(typename GraphType::VertexId)> pre_action, 
			function<void(typename GraphType::VertexId)> post_action) {
		typedef typename GraphType::VertexType VertexType;
		typedef typename GraphType::VertexId VertexId;

		if (srcV < 0 || srcV >= graph->NUM) throw std::invalid_argument("visit the illegal vertex id.");

		time++;
		VertexType* visit_vertex = graph->vertexes_.at(srcV);
		visit_vertex->found_time_ = time;
		visit_vertex->color_ = VertexType::Color::Gray;
		pre_action(srcV);

		const auto& adj_lists = graph->out_edge_of_vertex(srcV);
		for (auto i : adj_lists) {
			VertexId next_id = i.first;
			VertexType* next_vertex = graph->vertexes_.at(next_id);
			if (next_vertex->color_ != VertexType::Color::White) continue;
			next_vertex->p_ = visit_vertex;
			visit(next_id, graph, time, pre_action, post_action);
		}
		time++;
		visit_vertex->finish_time_ = time;
		visit_vertex->color_ = VertexType::Color::Black;
		post_action(srcV);
		}

		template<class GraphType>
		void DFS(const GraphType* graph, function<void(typename GraphType::VertexId)> root_pre_func, function<void(typename GraphType::VertexId)> root_post_func,
			function<void(typename GraphType::VertexId)> pre_action, function<void(typename GraphType::VertexId)> post_action,
			vector<typename GraphType::VertexId> search_order = vector<typename GraphType::VertexId>()) {
			int time = 0;
			for (auto i : graph->vertexes_) {
				if (!i) continue;
				i->color_ = GraphType::VertexType::Color::White;
				i->p_ = NULL;
			}
			vector<typename GraphType::VertexId> real_search_order;
			if (search_order.size() == 0) {
				for (int i = 0; i < GraphType::NUM; ++i) {
					if(graph->vertexes_[i])
						real_search_order.push_back(i);
				}
			}
			else
				real_search_order = search_order;

			for (auto i : real_search_order) {
				if (graph->vertexes_[i]->color_ == GraphType::VertexType::Color::White) {
					root_pre_func(graph->vertexes_[i]->id_);
					visit(graph->vertexes_[i]->id_, graph,time,pre_action, post_action);
					root_post_func(graph->vertexes_[i]->id_);
				}
			}
		}

		template<class GraphType>
		list<typename GraphType::VertexId> TopoSort(const GraphType* graph) {
			list<typename GraphType::VertexId> sorted_vertex_id;
			if (!graph) return sorted_vertex_id;
			function<void(typename GraphType::VertexId)> empty_func = [](typename GraphType::VertexId) {};
			function<void(typename GraphType::VertexId)> post_func = [&sorted_vertex_id](typename GraphType::VertexId id) {
				sorted_vertex_id.push_front(id);
			};
			DFS(graph, empty_func, empty_func, empty_func, post_func);
			return sorted_vertex_id;
		}

		template<class GraphType>
		vector<vector<typename GraphType::VertexId>> SCC(const GraphType* graph) {
			if (!graph) throw std::invalid_argument("graph is empty.");

			typedef typename GraphType::VertexId VertexId;
			typedef typename GraphType::VertexType VertexType;

			vector<VertexId> search_order;
			vector<vector<VertexId>> sccs;
			vector<VertexId> scc;
			function<void(VertexId)> post_func = [&search_order](VertexId id) {search_order.insert(search_order.begin(), id); };
			function<void(VertexId)> empty_func = [](VertexId) {};

			DFS(graph, empty_func, empty_func, empty_func, post_func);

			shared_ptr<GraphType> inverse_graph = graph->inverse();

			function<void(VertexId)> root_post_func = [&sccs, &scc](VertexId id) {sccs.push_back(scc); scc.clear(); };
			function<void(VertexId)> inverse_post_func = [&sccs, &scc](VertexId id) {scc.push_back(id); };
			DFS(&*inverse_graph, empty_func, root_post_func, empty_func, inverse_post_func, search_order);
			return sccs;
		}
	}
}
		
		

#endif // !BASIC_ALGORITHM_H
