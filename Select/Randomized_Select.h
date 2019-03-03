#pragma once
#include<vector>
#include"../Sort/QuickSort.h"

namespace CLRS {
	namespace Select {
		template<class Iterator,class Compare>
		Iterator Randomized_Select(Iterator begin, Iterator end, size_t rank,Compare compare) {		
			Iterator patition = CLRS::Sort::Randomized_Partition(begin, end, compare);
			size_t idx = std::distance(begin, patition);
			if (idx == rank) return patition;
			else if (idx > rank) return Randomized_Select(begin, patition, rank,compare);
			else return Randomized_Select(patition + 1, end, rank - idx - 1, compare);
		}
	}
}