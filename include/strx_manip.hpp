#ifndef _STRX_MANIP_H
#define _STRX_MANIP_H

#ifndef _STRING_
#ifndef _GLIBCXX_STRING
#include <string>
#endif
#endif
#ifndef _CSTRING_
#ifndef _GLIBCXX_cSTRING
#include <cstring>
#endif
#endif
#ifndef _VECTOR_
#ifndef _GLIBCXX_VECTOR
#include <vector>
#endif
#endif

namespace strx {
	/// <summary>
	/// String constant containing the common white-space characters.
	/// </summary>
	extern const char * whitespace;

	/// <summary>
	/// Checks if the given character exists within the provided string.
	/// </summary>
	/// <param name="str">String to be searched.</param>
	/// <param name="c">Character to search for.</param>
	/// <returns>true if the character is found; otherwise false.</returns>
	inline bool contains(const ::std::string_view &str, const char &c) { return str.find_first_of(c) != ::std::string::npos; }
	/// <summary>
	/// Checks if the given query exists within the provided target.
	/// </summary>
	/// <param name="target">Target string to be searched.</param>
	/// <param name="query">String to be searched for</param>
	/// <returns>true if the query is found; otherwise false.</returns>
	inline bool contains(const ::std::string_view &target, const ::std::string_view &query) { return target.find(query) != ::std::string::npos; }
	/// <summary>
	/// Checks if the provided string starts with the provided pattern.
	/// </summary>
	/// <param name="str">String to be checked.</param>
	/// <param name="pattern">String to look for.</param>
	/// <returns>true if the pattern is found; otherwise false</returns>
	inline bool starts_with(const ::std::string_view & str, const ::std::string_view &pattern) { return str.size() >= pattern.size() && str.find_first_of(pattern) == 0; }

	/// <summary>
	/// Searches the provided string and returns the index of the first occurrence of the provided <paramref name="pattern"/>.
	/// </summary>
	/// <param name="str">String to be searched.</param>
	/// <param name="pattern">Pattern to look for.</param>
	/// <returns>true if the pattern is found; otherwise false</returns>
	::std::size_t find_first_of_pat(const ::std::string_view &str, const ::std::string_view &pattern);
	/// <summary>
	/// Splits the provided string into an array of strings using a provided delimiter as the split point.
	/// </summary>
	/// <param name="str">String to be split.</param>
	/// <param name="delim">Delimiter to be split at and removed from the string.</param>
	/// <returns>Array of strings</returns>
	::std::vector<::std::string> split(::std::string str, const char &delim);

	/// <summary>
	/// Joins together an array of strings, using the provided delimiter to separate each token in the resulting string.
	/// </summary>
	/// <param name="tokens">Tokens to be joined into a single string.</param>
	/// <param name="delim">Delimiter to separate the tokens within the new string.</param>
	/// <returns>Single string of concatenated tokens and delimiters.</returns>
	::std::string join(const ::std::vector<::std::string> &tokens, const char &delim);
	/// <summary>
	/// Joins together an array of strings, using the provided delimiter to separate each token in the resulting string.
	/// </summary>
	/// <param name="tokens">Tokens to be joined into a single string.</param>
	/// <param name="delim">Delimiter to separate the tokens within the new string.</param>
	/// <returns>Single string of concatenated tokens and delimiters.</returns>
	::std::string join(const ::std::vector<::std::string> &tokens, const ::std::string_view &delim);

	/// <summary>
	/// Replaces portions of the provided string that match the patterns with the provided replacement string.
	/// </summary>
	/// <param name="str">String to be modified.</param>
	/// <param name="patterns">Array of patterns to look for.</param>
	/// <param name="length">Length of pattern array</param>
	/// <param name="replacement">Replacement string.</param>
	/// <returns>Modified string.</returns>
	::std::string replace(::std::string str, const ::std::string patterns[], ::std::size_t length, const ::std::string_view &replacement);
	/// <summary>
	/// Replaces portions of the provided string that match the pattern with the provided replacement.
	/// </summary>
	/// <param name="str">String to be modified.</param>
	/// <param name="patterns">Pattern to look for.</param>
	/// <param name="replacement">Replacement string.</param>
	/// <returns>Modified string.</returns>
	::std::string replace(::std::string str, const ::std::string_view &pattern, const ::std::string_view &replacement);
	/// <summary>
	/// Replaces the provided character in the given string with the provided replacement.
	/// </summary>
	/// <param name="str">String to be modified.</param>
	/// <param name="c">Character to be replaced.</param>
	/// <param name="replacement">Replacement string.</param>
	/// <returns>Modified string.</returns>
	::std::string replace(const ::std::string_view &str, const char &c, const ::std::string_view &replacement);
	/// <summary>
	/// Replaces the provided pattern in the given string with the provided replacement character.
	/// </summary>
	/// <param name="str">String to be modified.</param>
	/// <param name="pattern">pattern to look for.</param>
	/// <param name="replacement">Replacement character.</param>
	/// <returns>Modified string.</returns>
	::std::string replace(const ::std::string_view &str, const ::std::string_view &pattern, const char &replacement);
	/// <summary>
	/// Replaces the provided pattern character in the given string with the provided replacement character.
	/// </summary>
	/// <param name="str">String to be modified.</param>
	/// <param name="pattern">Character to be replaced.</param>
	/// <param name="replacement">Replacement character.</param>
	/// <returns>Modified string.</returns>
	::std::string replace(::std::string str, const char &pattern, const char &replacement);

	/// <summary>
	/// Left pads the given string to fit a minimum width. Empty space is filled with the provided <paramref name="pad"/>.
	/// </summary>
	/// <param name="str">String to be padded.</param>
	/// <param name="width">Width to pad to.</param>
	/// <param name="pad">Character to pad with (default: ' ')</param>
	/// <returns>Padded string</returns>
	inline ::std::string lpad(::std::string str, ::std::size_t width, const char pad = ' ')
	{
		if (width < str.size()) return str;
		width -= str.size();
		return width > 0 ? str.insert(0, width, pad) : str;
	}
	/// <summary>
	/// Right pads the given string to fit a minimum width. Empty space is filled with the provided <paramref name="pad"/>.
	/// </summary>
	/// <param name="str">String to be padded.</param>
	/// <param name="width">Width to pad to.</param>
	/// <param name="pad">Character to pad with (default: ' ')</param>
	/// <returns>Padded string</returns>
	inline ::std::string rpad(::std::string str, ::std::size_t width, const char pad = ' ')
	{
		size_t size = str.size();
		if (width < size) return str;
		width -= size;
		return width > 0 ? str.insert(size, width, pad) : str;
	}

	/// <summary>
	/// Trims any excess white-space characters off the left end of the string.
	/// </summary>
	/// <param name="str">String to be trimmed.</param>
	/// <returns>Trimmed string</returns>
	inline ::std::string ltrim(::std::string str)
	{
		if (str.size() == 0) return str;
		str.erase(str.begin(), str.begin() + str.find_first_not_of(whitespace));
		return str;
	}
	/// <summary>
	/// Trims any excess white-space characters off the right end of the string.
	/// </summary>
	/// <param name="str">String to be trimmed.</param>
	/// <returns>Trimmed string</returns>
	inline ::std::string rtrim(::std::string str)
	{
		if (str.size() == 0) return str;
		str.erase(str.begin() + str.find_last_not_of(whitespace) + 1, str.end());
		return str;
	}
	/// <summary>
	/// Trims any excess white-space characters off the ends of the string.
	/// </summary>
	/// <param name="str">String to be trimmed.</param>
	/// <returns>Trimmed string</returns>
	inline ::std::string trim(const ::std::string &str) { return rtrim(ltrim(str)); }

	/// <summary>
	/// Checks if the provided string is empty
	/// </summary>
	/// <param name="str">String to be checked.</param>
	/// <returns>true if the string is empty; otherwise false.</returns>
	inline bool s_empty(const ::std::string_view &str) { return str.size() == 0; }
	/// <summary>
	/// Checks if the provided string is empty or only filled with white-space characters.
	/// </summary>
	/// <param name="str">String to be checked.</param>
	/// <returns>true if the string is empty; otherwise false;</returns>
	inline bool s_whitespace(const ::std::string_view &str) { return str.size() == 0 || str.find_first_not_of(whitespace) != ::std::string::npos; }

	/// <summary>
	/// Converts all characters in the provided string to their lower case variants.
	/// </summary>
	/// <param name="str">String to be lower cased.</param>
	/// <returns>Lower cased string.</returns>
	::std::string str2lower(::std::string str);
	/// <summary>
	/// Converts all characters in the provided string to their upper case variants.
	/// </summary>
	/// <param name="str">String to be upper cased.</param>
	/// <returns>Lower cased string.</returns>
	::std::string str2upper(::std::string str);

	/// <summary>
	/// Converts the string to a boolean value based on its contents.
	/// </summary>
	/// <param name="str">String to be converted.</param>
	/// <returns>true if the string is equal to "true" or "1" (case insensitive).</returns>
	inline bool stob(::std::string str) {
		str = str2lower(trim(str));
		return str == "true" || str == "1";
	}
	/// <summary>
	/// Converts the given string to a single signed 8bit integer value.
	/// </summary>
	/// <param name="str">String to be converted.</param>
	/// <returns>Converted value.</returns>
	inline int8_t stobyte(::std::string str) { return (int8_t)stol(str); }
	/// <summary>
	/// Converts the given string to a single unsigned 8bit integer value.
	/// </summary>
	/// <param name="str">String to be converted.</param>
	/// <returns>Converted value.</returns>
	inline uint8_t stoubyte(::std::string str) { return (uint8_t)stoul(str); }

	/// <summary>
	/// Reads all the contents of the given file into an in-memory string.
	/// </summary>
	/// <param name="path">Path to the file to be read.</param>
	/// <returns>String containing all of the file's contents.</returns>
	::std::string ftos(::std::string path);
	/// <summary>
	/// Reads all the contents of the given file into an in-memory string.
	/// </summary>
	/// <param name="file">Pointer to the file to be read.</param>
	/// <returns>String containing all of the file's contents.</returns>
	::std::string ftos(FILE* file);
}
#endif