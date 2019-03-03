#pragma once

#include"../Sort/InsertSort.h"
#include"../Sort/QuickSort.h"
#include<vector>

namespace CLRS {
	namespace Select {

		template<class Iterator,class Compare>
		Iterator Good_Select(Iterator begin, Iterator end, size_t rank,Compare compare) {
			typedef typename std::iterator_traits<Iterator>::value_type T;

			assert(rank < std::distance(begin, end));
			if (std::distance(begin, end) == 1) return begin;

			std::vector<T> mid_val;
			auto iter = begin;
			while (iter < end) {
				auto from = iter;
				auto to = std::distance(from, end) > 5 ? from+5 : end;
				CLRS::Sort::InsertSort(from, to, compare);
				mid_val.push_back(*(from + (to - from) / 2));
				if (to == end) break;
				iter += 5;
			}

			Iterator mid_of_mid = Good_Select(mid_val.begin(), mid_val.end(), mid_val.size()/2,compare);
			T comp_val = *mid_of_mid;
			for (iter = begin; iter != end; iter++) {
				if (*iter == comp_val) break;
			}
			auto mid_iter = CLRS::Sort::Partition(begin, end, iter, compare);
			size_t mid_rank = std::distance(begin, mid_iter);
			if (mid_rank == rank) return mid_iter;
			if (mid_rank > rank) return Good_Select(begin, mid_iter,rank,compare);
			else return Good_Select(mid_iter + 1, end,rank - mid_rank - 1, compare);
		}
	}
}