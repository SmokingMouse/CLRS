#pragma once

namespace CLRS {
	namespace Sort {
		template<class Iterator,class Compare>
		void InsertSort(Iterator begin, Iterator end, Compare compare) {
			for (Iterator iter = begin; iter != end; ++iter) {
				Iterator temp_iter = iter;
				while (temp_iter > begin && compare(*temp_iter, *(temp_iter - 1))) {
					std::swap(*temp_iter, *(temp_iter - 1));
					--temp_iter;
				}
			}
		}
	}
}