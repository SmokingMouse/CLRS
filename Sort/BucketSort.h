#pragma once

#include<vector>
#include"QuickSort.h"

namespace CLRS {
	namespace Sort {
		template<class Iterator,class Compare>
		void BucketSort(Iterator begin, Iterator end, Compare compare,typename std::iterator_traits<Iterator>::value_type min) {
			typedef typename std::iterator_traits<Iterator>::value_type T;
			
			const int Bucket_Num = 10;
			std::vector<T> bucktes[Bucket_Num];

			for (auto iter = begin; iter != end; ++iter) {
				T idx = (*iter - min) / Bucket_Num;
				bucktes[idx].push_back(*iter);
			}

			int insert_total = 0;
			for (int i = 0; i < Bucket_Num; i++) {
				if(!bucktes[i].empty())
					QuickSort(bucktes[i].begin(), bucktes[i].end(), compare);
				std::copy(bucktes[i].begin(), bucktes[i].end(), begin + insert_total);
				insert_total += bucktes[i].size();
			}

		}
	}
}