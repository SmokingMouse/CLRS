#pragma once

#include<vector>
#include"InsertSort.h"
namespace CLRS {
	namespace Sort {
		template<class T>
		T Nth_Digit(T data,size_t N) {
			static_assert(std::is_integral<T>::value, "Type must be inergral.");
			return data / (T)std::pow(10,N) - data / (T)std::pow(10,N + 1) * 10;
		}

		template<class Iterator,class Compare>
		void RadixSort(Iterator begin, Iterator end, Compare compare,size_t width) {
			typedef typename Iterator::value_type T;

			int distance = std::distance(begin, end);
			if (distance <= 0) return;

			size_t i = 0;
			
			auto comp = [&i,&compare](const T& l, const T& r) {
				return compare(Nth_Digit(l,i), Nth_Digit(r,i));
			};

			for (;i < width; i++) {
				InsertSort<Iterator>(begin, end, comp);
			}
		}
	}
}