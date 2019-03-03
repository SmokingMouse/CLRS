#pragma once

#include <random>
#include <ctime>
#include<vector>

namespace CLRS {
	namespace Sort {
		template<class Iterator,class Compare>
		Iterator Randomized_Partition(Iterator begin, Iterator end, Compare compare) {
			auto distance = std::distance(begin, end);
			if (begin == end) return end;

			std::default_random_engine engine(time(NULL));
			std::uniform_int_distribution<int> generate(0,distance-1);
			auto idx = generate(engine);
			std::swap(*(begin + idx), *(begin + distance - 1));
			return Partition(begin, end, compare);
		}

		template<class Iterator,class Compare>
		void QuickSort(Iterator begin, Iterator end, Compare compare) {
			Iterator iter = Randomized_Partition(begin, end,compare);
			if (iter == end) return;
			QuickSort(begin, iter, compare);
			QuickSort(iter + 1,end, compare);
		}

		template<class Iterator,class Compare>
		Iterator Partition(Iterator begin, Iterator end, Compare compare) {
			using ValueType = typename Iterator::value_type;

			if (begin == end) return end;
			ValueType comp_val = *(end-1);
			auto next_pos = begin;
			for (auto iter = begin; iter != end-1; iter++) {
				if (compare(*iter, comp_val)) {
					std::swap(*iter, *(next_pos++));
				}
			}
			std::swap(*(end-1), *next_pos);
			return next_pos;
		}

		template<class Iterator,class Compare>
		Iterator Partition(Iterator begin, Iterator end, Iterator comp_iter, Compare compare) {
			if (begin == end) return end;
			std::swap(*(end - 1), *(comp_iter));
			return Partition(begin, end, compare);
		}
	}
}