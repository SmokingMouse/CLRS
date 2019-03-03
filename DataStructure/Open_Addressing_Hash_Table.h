#pragma once

#include<array>
#include<functional>
#include"Chained_Hash_Table.h"
namespace CLRS {
	namespace DataStructure {

		template<size_t N>
		size_t Linear_Probing_Int(int i, size_t cnt) {
			return (Int_Div_Hash(i, N) + cnt) % N;
		}

		template<size_t N>
		size_t Quadratic_Probing_Int(int i, size_t cnt) {
			return (Int_Div_Hash(i, N) + cnt + cnt ^ 2) % N;// The h(i,N)+ c1 * cnt + c2 * cnt^2.
		}

		template<size_t N>
		size_t Double_Probing_Int(int i, size_t cnt) {
			return (Int_Div_Hash(i, N) + cnt * Int_Mul_Hash(i, N)) % N;// h1(i,N)+h2(i,N)*cnt.
		}

		template<class KeyType,size_t N>
		class Open_Addressing_Hash_Table {
		public:
			typedef KeyType* KeyPtr;

			Open_Addressing_Hash_Table() { elem_size_ = 0; for (auto& item : hash_table_) item = NULL; }
			Open_Addressing_Hash_Table(std::function <size_t(KeyType, size_t)> hash_func) {
				elem_size_ = 0;
				hash_func_ = hash_func;
				for (auto& item : hash_table_) item = NULL;
			}

			void Insert(const KeyType& key) {
				size_t cnt = 0;
				while (cnt < N) {
					size_t idx = hash_func_(key, cnt);
					if (hash_table_[idx] == NULL) {
						hash_table_[idx] = new KeyType(key);
						elem_size_++;
						return;
					}
					cnt++;
				}
				throw std::out_of_range("The table is full.");
			}

			//Doesn't sign the DELETED.
			bool Search(const KeyType& key) {
				size_t cnt = 0;
				while (cnt < N) {
					size_t idx = hash_func_(key, cnt);
					if (hash_table_[idx] && *hash_table_[idx] == key) return true;
					cnt++;
				}
				return false;
			}

			void Delete(const KeyType& key) {
				size_t cnt = 0;
				while (cnt < N) {
					size_t idx = hash_func_(key, cnt);
					if (hash_table_[idx] && *hash_table_[idx] == key) {
						delete hash_table_[idx];
						hash_table_[idx] = NULL;
						elem_size_--;
						return;
					}
				}

			}
		private:
			std::array<KeyPtr, N> hash_table_;
			size_t elem_size_;
			std::function <size_t(KeyType, size_t)> hash_func_;
		};
	}
}