#pragma once

#include<vector>

namespace CLRS {
	namespace Sort {
		template<class Iterator,class Compare>
		void MergeSort(Iterator begin, Iterator end, Compare compare) {
			auto size = std::distance(begin, end);

			if (size <= 1) return;
			Iterator middle = begin + size / 2;
			MergeSort(begin, middle, compare);
			MergeSort(middle, end, compare);
			Merge(begin, middle, end, compare);
		}

		template<class Iterator,class Compare>
		void Merge(Iterator begin, Iterator middle, Iterator end, Compare compare) {
			Iterator left_iter = begin;
			Iterator right_iter = middle;
			auto distance = std::distance(begin, end);
			std::vector<typename Iterator::value_type> temp_store;
			Iterator iter;
			auto cnt = distance;
			while (cnt-- > 0) {
				if (left_iter != middle && right_iter != end) {
//					iter = compare(*left_iter, *right_iter) ? left_iter++ : right_iter++;
					if (compare(*left_iter, *right_iter)) {
						iter = left_iter++;
					}
					else
						iter = right_iter++;
				}
				else if (left_iter == middle)  iter = right_iter++;
				else iter = left_iter++;
				temp_store.push_back(*iter);
			}
			for (int i = 0; i < distance; i++) {
				*(begin + i) = temp_store[i];
			}
		}
	}
}