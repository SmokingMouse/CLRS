#pragma once

#include<array>

namespace CLRS {
	namespace DataStructure {
		/*
		除法散列法
			N的选择最好是不太接近2的整数幂的素数.
		*/

		size_t Int_Div_Hash(int i,size_t N) {
			return i % N;
		}


		/*
		乘法散列法
		h(x) = m * (x * k mod 1).
		*/

		size_t Int_Mul_Hash(int i,size_t N) {
			double frac = (double)(i*0.618) - (int)(i*0.618);
			return N * frac;
		}

		template<class KeyType>
		struct Chained_Hash_Node {
			typedef Chained_Hash_Node<KeyType>* NodePtr;

			Chained_Hash_Node() :key_() { next_node_ = NULL; }
			Chained_Hash_Node(KeyType key, NodePtr p) :key_(key) { next_node_ = p; }

			KeyType key_;
			NodePtr next_node_;
		};

		template<class KeyType,class HashFunc,size_t N>
		class Chained_Hash_Table {
		public:
			typedef Chained_Hash_Node<KeyType> Node;
			typedef typename Node::NodePtr NodePtr;

			Chained_Hash_Table() { 
				elem_size_ = 0; 
				for (int i = 0; i < N;i++) hash_table_[i] = NULL;
			}
			Chained_Hash_Table(HashFunc f) :hash_func_(f) { 
				elem_size_ = 0; 
				for (int i = 0; i < N; i++) hash_table_[i] = NULL;
			}

			void Insert(const KeyType& key) {
				size_t idx = hash_func_(key,N);
				hash_table_[idx] = new Node(key, hash_table_[idx]);
				elem_size_++;
			}

			bool Search(const KeyType& key) {
				size_t idx = hash_func_(key,N);
				auto iter = hash_table_[idx];
				while (iter) {
					if (iter->key_ == key) return true;
				}
				return false;
			}

			void Delete(const KeyType& key) {
				size_t idx = hash_func_(key,N);
				auto iter = hash_table_[idx];
				NodePtr pre = NULL;
				while (iter) {
					if (iter->key_ == key) break;
					pre = iter;
					iter = iter->next_node_;
				}
				if (!iter) return;
				
				if (!pre) hash_table_[idx] = iter->next_node_;
				else pre->next_node_ = iter->next_node_;
				delete iter;
				elem_size_--;
			}
		private:
			std::array<NodePtr, N> hash_table_;
			HashFunc hash_func_;
			size_t elem_size_;
		};
	}
}