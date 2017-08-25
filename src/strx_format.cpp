#define _CRT_SECURE_NO_WARNINGS 1
#include "../include/strx_format.hpp"

using namespace std;
namespace strx {
	format::__end format::end = format::__end();
	format::__endclr format::endclr = format::__endclr();

	string format::str() const {
		string result = _buffer;
		string index;
		char buff[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
		for (size_t c = 0, size = _params.size(); c < size; c++) {
			sprintf(buff, "%zd", c);
			index = '{';
			index += buff;
			index += '}';
			result = strx::replace(result, index, _params[c]);
		}
		return result;
	}
	string format::strclr() {
		string result = str();
		clear();
		return result;
	}
}
#undef _CRT_SECURE_NO_WARNINGS