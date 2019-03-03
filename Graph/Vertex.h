#pragma once

namespace CLRS {
	namespace Graph {
		template<class KType>
		struct Ordinary_Vertex {
			typedef int VertexId;
			typedef Ordinary_Vertex VertexType;
			typedef KType KeyType;

			VertexId id_;
			KeyType key_;

			Ordinary_Vertex(const KType& key, VertexId id) :key_(key) { id_ = id; }
		};

		template<class KType>
		struct DFS_Vertex : public Ordinary_Vertex<KType>
		{
			typedef Ordinary_Vertex<KType>::VertexId VertexId;
			typedef DFS_Vertex VertexType;
			typedef Ordinary_Vertex<KType>::KeyType KeyType;

			enum Color{White,Gray,Black};

			DFS_Vertex() = default;
			DFS_Vertex(const KType& key, VertexId id) :Ordinary_Vertex<KType>(key,id){
				p_ = NULL;
				found_time_ = -1;
				finish_time_ = -1;
				color_ = White;
			}

			VertexType* p_;
			int found_time_;
			int finish_time_;
			Color color_;
		};

		template<class KType>
		struct BFS_Vertex :public Ordinary_Vertex<KType>{
			typedef Ordinary_Vertex<KType>::VertexId VertexId;
			typedef BFS_Vertex VertexType;
			typedef Ordinary_Vertex<KType>::KeyType KeyType;

			enum Color { White, Gray, Black };

			BFS_Vertex() = default;
			BFS_Vertex(const KType& key, VertexId id) :Ordinary_Vertex<KType>(key,id) {
				color_ = White;
				p_ = NULL;
				distance_ = 0;
			}

			void set_found(VertexType* p) {
				color_ = Gray;
				p_ = p;
				distance_ = p->distance_ + 1;
			}

			Color color_;
			VertexType* p_;
			int distance_;
		};

		template<class KType>
		struct Path_Vertex :public Ordinary_Vertex<KType> {
			typedef int Distance;
			typedef int VertexId;
			typedef Distance Key;

			Path_Vertex() = default;
			Path_Vertex(const KType& key, VertexId id) :Ordinary_Vertex<KType>(key, id){}

			Distance distance_;
			Path_Vertex* p_;
		};

		template<class KType>
		struct Dag_Vertex :public DFS_Vertex<KType> {
			typedef int Distance;
			typedef int VertexId;
			typedef Distance Key;

			Dag_Vertex() = default;
			Dag_Vertex(const KType& key,VertexId id):DFS_Vertex<KType>(key,id){}

			Distance distance_;
			Dag_Vertex* p_;
		};
	}
}

