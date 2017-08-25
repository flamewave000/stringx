#define _CRT_SECURE_NO_WARNINGS 1
#include "../include/strx_manip.hpp"
#include <sstream>
#include <cstdio>

using namespace std;

namespace strx {
	const std::string whitespace = " \n\r\t\v\f";

	size_t find_first_of_pat(const std::string &str, const std::string &pattern)
	{
		size_t c = 0, i = 0, size = str.size(), psize = pattern.size();
		if (size == 0 || psize == 0) {
			return string::npos;
		}
		size_t pos = string::npos;
		for (; c < size; c++) {
			if (pattern[0] == str[c]) {
				pos = c;
				for (i = 0; i < psize; i++) {
					if (pattern[i] != str[c + i]) {
						pos = string::npos;
						break;
					}
				}
				if (pos != string::npos) {
					return pos;
				}
			}
		}
		return string::npos;
	}

	vector<string> split(string str, const char &delim)
	{
		vector<string> tokens;
		for (size_t c = str.find_first_of(delim); c != string::npos; c = str.find_first_of(delim))
		{
			tokens.push_back(str.substr(0, c));
			str.erase(0, c + 1);
		}
		if (str.size() > 0)
		{
			tokens.push_back(str);
		}
		return tokens;
	}

	string join(const vector<string> &tokens, const char &delim)
	{
		ostringstream sstream;
		bool first = true;
		for (auto token : tokens)
		{
			if (!first) sstream << delim;
			else first = false;
			sstream << token;
		}
		return sstream.str();
	}
	string join(const vector<string> &tokens, const string &delim)
	{
		ostringstream sstream;
		bool first = true;
		for (auto token : tokens)
		{
			if (!first) sstream << delim;
			else first = false;
			sstream << token;
		}
		return sstream.str();
	}
	std::string replace(const std::string &str, const std::string *patterns, size_t length, const std::string &replacement)
	{
		string buff = "";
		size_t c = 0, psize;
		size_t offset = 0;
		const string *pattern;
		string src = str;
		for (size_t i = 0; i < length; i++)
		{
			c = 0;
			pattern = patterns + i;
			psize = pattern->size();
			while ((c = src.find_first_of(*pattern)) != str.npos)
			{
				buff += src.substr(offset, c);
				buff += replacement;
				offset = c + psize;
			}
			if (offset < src.size()) {
				buff += src.substr(offset);
			}
			src = buff;
			buff = "";
		}
		return src;
	}
	string replace(const string &str, const string &pattern, const string &replacement)
	{
		string result(str);
		size_t c = 0, psize = pattern.size();
		while ((c = find_first_of_pat(result, pattern)) != result.npos)
		{
			result = result.replace(c, psize, replacement);
		}
		return result;
	}
	string replace(const string &str, const char &pattern, const string &replacement)
	{
		string result = "";
		size_t c = 0;
		size_t offset = 0;
		while ((c = str.find_first_of(pattern)) != str.npos)
		{
			result += str.substr(offset, c);
			result += replacement;
			offset = c + 1;
		}
		if (offset < str.size()) {
			result += str.substr(offset);
		}
		return result;
	}
	string replace(const string &str, const string &pattern, const char &replacement)
	{
		string result = "";
		size_t c = 0;
		size_t offset = 0;
		while ((c = str.find_first_of(pattern)) != str.npos)
		{
			result += str.substr(offset, c);
			result += replacement;
			offset = c + 1;
		}
		if (offset < str.size()) {
			result += str.substr(offset);
		}
		return result;
	}
	string replace(const string &str, const char &pattern, const char &replacement)
	{
		string result(str);
		size_t size = result.size();
		const char *cstr = result.c_str();
		const void *c = nullptr;
		while ((c = memchr(cstr, replacement, size)) != nullptr) {
			*((char*)c) = replacement;
		}
		return result;
	}

	string str2lower(string str) {
		for (size_t c = 0, size = str.size(); c < size; c++) {
			if (str[c] >= 'A' && str[c] <= 'Z') {
				str[c] = str[c] ^ ' ';
			}
		}
		return str;
	}
	string str2upper(string str) {
		for (size_t c = 0, size = str.size(); c < size; c++) {
			if (str[c] >= 'a' && str[c] <= 'z') {
				str[c] = str[c] | ' ';
			}
		}
		return str;
	}

	string ftos(string path) {
		FILE * file = fopen(path.c_str(), "r");
		if (file != nullptr) {
			char buff[256];
			memset(buff, 0, 256);
			size_t read = 0;
			string result = "";
			while (true) {
				read = fread(buff, sizeof(char), 256, file);
				if (read <= 0) {
					break;
				}
				result += string(buff, read);
			}
			return move(result);
		}
		return "";
	}
	string ftos(FILE* file) {
		char buff[256];
		memset(buff, 0, 256);
		size_t read = 0;
		string result = "";
		while (true) {
			read = fread(buff, sizeof(char), 256, file);
			if (read <= 0) {
				break;
			}
			result += string(buff, read);
		}
		return move(result);
	}
}
#undef _CRT_SECURE_NO_WARNINGS