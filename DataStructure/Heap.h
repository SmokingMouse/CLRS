#pragma once

#include<vector>
#include<limits>
#include<functional>
#include<string>
namespace CLRS {
	namespace DataStructure {
		using std::vector;
		using std::function;


		template<class Type>
		struct GetType { typedef typename Type::Key Type; };

		template<>
		struct GetType<int> { typedef int Type; };

		template<>
		struct GetType<std::string> { typedef std::string Type; };

		template<class Type>
		struct GetType<Type*> { typedef typename GetType<Type>::Type Type; };

		template<class KType>
		class Heap {
		public:
			typedef typename GetType<KType>::Type Key;
			typedef function<bool(const KType& l, const KType& r)> Compare;
			typedef function <Key&(KType&)> KeyValue;

			//Heap():heap_(),bottom_(0){}
			//Heap(const vector<KType>& data) :heap_(data),bottom_(heap_.size()),compare_() {buildHeap();}
			Heap(const vector<KType>& data, Compare compare, KeyValue keyValue) :heap_(data), bottom_(heap_.size()),
				compare_(compare), keyValue_(keyValue)
			{
				buildHeap();
			}

			size_t heapSize() { return bottom_; }

			void buildHeap() {
				for (int idx = bottom_ / 2 - 1; idx >= 0; idx--) {
					adjust(idx);
				}
			}

			void adjust(size_t idx) {
				if (idx < 0 || idx >= bottom_) return;
				size_t left = idx * 2 + 1;
				size_t right = idx * 2 + 2;
				size_t largest;
				if (left < bottom_ && compare_(heap_[left],heap_[idx])) {
					largest = left;
				}
				else largest = idx;
				if (right < bottom_ && compare_(heap_[right], heap_[largest])) {
					largest = right;
				}
				if (largest != idx) {
					std::swap(heap_[idx], heap_[largest]);
					adjust(largest);
				}
			}

			KType top() {
				if (bottom_) return heap_[0];
				throw std::out_of_range("the heap is null.");
			}

			KType extract() {
				if (!bottom_) throw std::out_of_range("the heap is null.");
				KType result = heap_[0];
				std::swap(heap_[0], heap_[bottom_ - 1]);
				bottom_--;
				adjust(0);
				return result;
			}
			void increase(function<bool(const KType& key)> search,
				const Key& inc) {
				int target;
				for (int i = 0; i < bottom_; i++) {
					if (search(heap_[i])) {
						target = i;
						break;
					}
				}
				keyValue_(heap_[target]) = inc;
				downTopAdjust(target);
			}


			void downTopAdjust(int idx) {
				if (idx < 0 || idx >= bottom_) return;
				int target = idx;
				int p = (target - 1) / 2;
				while (p >= 0 && compare_(heap_[target], heap_[p])) {
					std::swap(heap_[target], heap_[p]);
					target = p;
					p = (target - 1) / 2;
				}
			}

			void insert(const KType& key) {
				if (heap_.size() == bottom_) heap_.push_back(key);
				else heap_[bottom_] = key;
				bottom_++;
				downTopAdjust(bottom_ - 1);
			}

			bool search(const KType& key) {
				for (int i = 0; i < bottom_; i++) {
					if (heap_[i] == key) return true;
				}
				return false;
			}

		private:
			vector<KType> heap_;
			Compare compare_;// function<bool(const KType& l,const KType& r)>
			KeyValue keyValue_;
			size_t bottom_;
		};

		
	}
}

