#pragma once

#include<iterator>

namespace CLRS {
	namespace Sort {
		template<class Iterator,class Compare>
		void BubbleSort(Iterator begin, Iterator end, Compare compare) {
			auto size = std::distance(begin, end);
			for (int i = 0; i < size - 1; i++) {
				for (Iterator iter = begin; iter < end-i-1; ++iter) {
					if (!compare(*iter, *(iter + 1))) std::swap(*iter, *(iter + 1));
				}
			}
		}
	}
}