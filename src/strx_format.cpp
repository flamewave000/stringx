#define _CRT_SECURE_NO_WARNINGS 1
#include "../include/strx_format.hpp"
#include <stdexcept>

using namespace std;

namespace strx
{
	string format::str() {
		if (!_is_dirty) return _val;
		size_t first = string::npos, param_size = _params.size();
		string buffer = _fmt;
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
				// Extract the index number of the format token
				string index_str = buffer.substr(first + 1, (c - first) - 1);
				// Convert the index string to an integer
				size_t index = (size_t)stoull(index_str, nullptr, 10);
				// Safety check index is within range
				if (index < 0 || index >= param_size) {
					throw range_error("format index '" + index_str + "' out of range for provided parameter list");
					return "";
				}
				// Replace the bracketed index with the referenced parameter
				buffer = buffer.replace(first, (c - first) + 1, _params[index]);
				// Adjust index end of replacement
				c = (first - 1) + _params[index].size();
				size = buffer.size();
				first = string::npos;
			}
			// If we hit a non decimal character, then our formatter token breaks and is ignored.
			else if (first != string::npos && (buffer[c] > '9' || buffer[c] < '0')) {
				first = string::npos;
			}
		}
		_is_dirty = false;
		return _val = buffer;
	}
	string format::strclr() {
		string result = str();
		clear();
		return result;
	}
}
#undef _CRT_SECURE_NO_WARNINGS