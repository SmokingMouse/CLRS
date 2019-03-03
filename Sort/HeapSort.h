#include"../DataStructure/Heap.h"
#include<vector>

namespace CLRS {
	namespace Sort {
		template<class Iterator,class Compare>
		void HeapSort(Iterator begin, Iterator end, Compare compare) {
			using DataType = typename Iterator::value_type;
			
			std::vector<DataType> temp(begin, end);
			auto keyOfValue = [](DataType& i)->DataType& {return i; };
			
			CLRS::DataStructure::Heap<DataType> heap(temp,compare,keyOfValue);
			
			for (auto iter = begin; iter != end; ++iter) {
				*iter = heap.extract();
			}
		}
	}
}