#define _CRT_SECURE_NO_WARNINGS 1
#include "strx_format.hpp"

#ifndef _STDEXCEPT_
#ifndef _GLIBCXX_STDEXCEPT
#include <stdexcept>
#endif
#endif

using namespace std;

namespace strx
{
	enum index_type {
		none,
		generic,
		numbered
	};
	string format::str() {
		if (!is_dirty()) return _val;
		size_t first = string::npos, param_size = _params.size();
		string buffer = _fmt;
		index_type indexing = index_type::none;
		size_t generic_indexer = 0;
		for (size_t c = 0, size = buffer.size(); c < size; c++) {
			// If we find the start of an index token
			if (buffer[c] == '{') {
				// If this is the first found
				if (first == string::npos) first = c;
				// Otherwise this is a second one and the bracket should now be escaped
				else {
					buffer.erase(c);
					first = string::npos;
				}
			}
			// If we have found the last one
			else if (buffer[c] == '}' && first != string::npos) {
				size_t index = SIZE_T_MAX;
				if (indexing == index_type::numbered) {
					// Extract the index number of the format token
					string index_str = buffer.substr(first + 1, (c - first) - 1);
					// Convert the index string to an integer
					index = (size_t)stoull(index_str, nullptr, 10);
					// Safety check index is within range
					if (index == SIZE_T_MAX || (index >= param_size && index < SIZE_T_MAX)) {
						throw range_error("format index '" + (index_str)+"' out of range for provided parameter list");
						return "";
					}
				}
				else if (indexing == index_type::generic) {
					index = generic_indexer++;
					// Safety check index is within range
					if (index == SIZE_T_MAX || (index >= param_size && index < SIZE_T_MAX)) {
						throw range_error("format index out of range for provided parameter list");
						return "";
					}
				}
				else {
					throw runtime_error("invalid state");
					return "";
				}
				// Replace the bracketed index with the referenced parameter
				buffer = buffer.replace(first, (c - first) + 1, _params[index]);
				// Adjust index end of replacement
				c = (first - 1) + _params[index].size();
				size = buffer.size();
				first = string::npos;
			}
			else if (first != string::npos) {
				if (indexing != index_type::generic && buffer[c] == '#') {
					if (indexing == index_type::numbered) {
						throw logic_error("cannot mix numbered and generic indexing");
						return "";
					}
					indexing = index_type::generic;
				}
				else if (indexing != index_type::numbered && buffer[c] <= '9' && buffer[c] >= '0') {
					if (indexing == index_type::generic) {
						throw logic_error("cannot mix numbered and generic indexing");
						return "";
					}
					indexing = index_type::numbered;
				}
				// If we hit a non numbered/generic index character, then our formatter token breaks and is ignored.
				else if((buffer[c] > '9' || buffer[c] < '0') && buffer[c] != '#') {
					first = string::npos;
				}
			}
		}
		return _val = buffer;
	}
	string format::strclr() {
		string result = str();
		clear();
		return std::move(result);
	}
}
#undef _CRT_SECURE_NO_WARNINGS
