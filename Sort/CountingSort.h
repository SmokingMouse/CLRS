#pragma once

#include<vector>
namespace CLRS {
	namespace Sort {
		template<class Iterator>
		void CountingSort(Iterator begin, Iterator end, typename std::iterator_traits<Iterator>::value_type max) {
			typedef typename std::iterator_traits<Iterator>::value_type T;
			static_assert(std::is_integral<T>::value, "This algorithm only suits type int.");

			int distance = std::distance(begin, end);
			if (distance == 0) return;
			std::vector<int> cntOfVal(max + 1,0);
			for (auto iter = begin; iter != end; ++iter) {
				cntOfVal[*iter]++;
			}

			for (int i = 1; i < max + 1;i++) {
				cntOfVal[i] += cntOfVal[i - 1];
			}
			std::vector<T> result(distance);
			int offset = distance - 1;
			while (offset >= 0) {
				T val = *(begin + offset);
				result[--cntOfVal[val]] = val;
				offset--;
			}
			for (int idx = 0; idx < distance; idx++) {
				*(begin + idx) = result[idx];
			}
		}
	}
}