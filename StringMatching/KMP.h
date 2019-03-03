#pragma once

#include<vector>
#include<string>
namespace CLRS {
	namespace StringMatching {
		using std::vector;
		using std::string;

		vector<size_t> Compute_Prefix_Function(const string& pattern) {
			vector<size_t> result;
			auto pattern_size = pattern.size();
			if (!pattern_size) return result;
			result.push_back(0);
			size_t p = 0;

			for (size_t idx = 1; idx < pattern_size; idx++) {
				while (p > 0 && pattern[p] != pattern[idx]) {
					p = result[p - 1];
				}
				if (pattern[p] == pattern[idx]) p++;
				result.push_back(p);
			}
			return result;
		}

		vector<size_t> KMP(const string& text, const string& pattern) {
			vector<size_t> pai = Compute_Prefix_Function(pattern);
			vector<size_t> result;
			auto text_size = text.size();
			auto pattern_size = pattern.size();
			if (!pattern_size) return result;
			size_t p = 0;
			for (size_t idx = 0; idx < text_size; idx++) {
				while (p > 0 && pattern[p] != text[idx]) {
					p = pai[p-1];
				}
				if (pattern[p] == text[idx]) p++;
				if (p == pattern_size) result.push_back(idx - p + 1);
			}
			return result;
		}

		
	}
}