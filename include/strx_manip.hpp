#ifndef _STRX_MANIP_H
#define _STRX_MANIP_H

#include <string>
#include <cstring>
#include <vector>

namespace strx {
	extern const ::std::string whitespace;

	inline bool contains(const ::std::string &str, const char &c) { return str.find_first_of(c) != ::std::string::npos; }
	inline bool contains(const ::std::string &target, const ::std::string &query) { return target.find(query) != ::std::string::npos; }
	inline bool starts_with(const ::std::string & str, const ::std::string &pattern) { return str.size() >= pattern.size() && str.find_first_of(pattern) == 0; }


	::std::size_t find_first_of_pat(const ::std::string &str, const ::std::string &pattern);
	::std::vector<::std::string> split(::std::string str, const char &delim);

	::std::string join(const ::std::vector<::std::string> &tokens, const char &delim);
	::std::string join(const ::std::vector<::std::string> &tokens, const ::std::string &delim);

	::std::string replace(const ::std::string &str, const ::std::string *patterns, ::std::size_t length, const ::std::string &replacement);
	::std::string replace(const ::std::string &str, const ::std::string &pattern, const ::std::string &replacement);
	::std::string replace(const ::std::string &str, const char &c, const ::std::string &replacement);
	::std::string replace(const ::std::string &str, const ::std::string &pattern, const char &replacement);
	::std::string replace(const ::std::string &str, const char &pattern, const char &replacement);

	inline ::std::string lpad(::std::string str, ::std::size_t width, const char pad = ' ')
	{
		width -= str.size();
		return width > 0 ? str.insert(0, width, pad) : str;
	}
	inline ::std::string rpad(::std::string str, ::std::size_t width, const char pad = ' ')
	{
		size_t size = str.size();
		width -= size;
		return width > 0 ? str.insert(size, width, pad) : str;
	}

	inline ::std::string ltrim(::std::string str)
	{
		if (str.size() == 0) return str;
		str.erase(str.begin(), str.begin() + str.find_first_not_of(whitespace));
		return str;
	}
	inline ::std::string rtrim(::std::string str)
	{
		if (str.size() == 0) return str;
		str.erase(str.begin() + str.find_last_not_of(whitespace) + 1, str.end());
		return str;
	}
	inline ::std::string trim(const ::std::string &str)
	{
		return rtrim(ltrim(str));
	}

	inline bool s_empty(const ::std::string &str) { return str.size() == 0; }
	inline bool s_whitespace(const ::std::string &str) { return str.size() == 0 || str.find_first_not_of(whitespace) != ::std::string::npos; }

	::std::string str2lower(::std::string str);
	::std::string str2upper(::std::string str);

	inline bool stob(::std::string str) {
		str = trim(str);
		return str == "true" || str == "True" || str == "1";
	}
	inline int8_t stobytec(::std::string str) { return (int8_t)stol(str); }
	inline uint8_t stoubyte(::std::string str) { return (uint8_t)stoul(str); }

	::std::string ftos(::std::string path);
	::std::string ftos(FILE* file);
}
#endif