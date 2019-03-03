#pragma once

#include<string>
#include<vector>

namespace CLRS {
	namespace StringMatching {

		using std::string;
		using std::vector;


		/*
		Complexity O((n-m+1)*m)
		*/
		vector<size_t> Regular_Matching(const string& text, const string& pattern) {
			vector<size_t> result;
			auto text_size = text.size();
			auto pattern_size = pattern.size();
			if (!text_size || !pattern_size||pattern_size > text_size) return result;
			for (size_t idx = 0; idx < text_size - pattern_size + 1; idx++) {
				size_t offset = 0;
				for(;offset < pattern_size; offset++) {
					if (text[idx + offset] != pattern[offset]) break;
				}
				if (offset == pattern_size) result.push_back(idx);
			}
			return result;
		}
	}
}