#define _CRT_SECURE_NO_WARNINGS 1
#include "../include/strx_format.hpp"

using namespace std;
namespace strx {
	string format::str() {
		if (_is_dirty) {
			_is_dirty = false;
			string result = _fmt;
			char buff[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
			for (size_t c = 0, size = _params.size(); c < size; c++) {
				sprintf(buff, "{%zd}", c);
				// TODO: Handle bracket escaping. '{{0}' should print as '{0}' and not formatted.
				result = strx::replace(result, buff, _params[c]);
			}
			_val = move(result);
		}
		return _val;
	}
	string format::strclr() {
		string result = str();
		clear();
		return result;
	}
}
#undef _CRT_SECURE_NO_WARNINGS