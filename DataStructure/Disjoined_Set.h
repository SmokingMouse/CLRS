#pragma once

#include<memory>

namespace CLRS {
	namespace DataStructure {
		using std::shared_ptr;
		
		template<class KType>
		struct Disjoined_Set_Node {
			typedef shared_ptr<Disjoined_Set_Node> ParentPtr;
			typedef int Rank;

			Disjoined_Set_Node(KType key) :key_(key) {
				rank_ = 0;
				p_ = NULL;
			}

			Rank rank_;
			ParentPtr p_;
			KType key_;
		};


		template<class KType>
		void Make_Set(shared_ptr<Disjoined_Set_Node<KType>> node) {
			node->rank_ = 0;
			node->p_ = node;
		}

		template<class KType>
		void Union(shared_ptr<Disjoined_Set_Node<KType>> l, 
			shared_ptr<Disjoined_Set_Node<KType>> r) {
			auto set_l = Find_Set(l);
			auto set_r = Find_Set(r);
			if (set_l != set_r) {
				if (set_l->rank_ > set_r->rank_) {
					set_r->p_ = set_l;
				}
				else {
					set_l->p_ = set_r;
					if (set_l->rank_ == set_r->rank_)
						set_r->rank_++;
				}
			}
		}
		
		template<class KType>
		shared_ptr<Disjoined_Set_Node<KType>> Find_Set
		(shared_ptr<Disjoined_Set_Node<KType>> x) {
			if (x != x->p_) {
				x->p_ = Find_Set(x->p_);
			}
			return x->p_;
		}

	}
}

