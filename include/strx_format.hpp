#ifndef _STRX_FORMAT_H
#define _STRX_FORMAT_H

#ifndef _STRX_MANIP_H
#include "strx_manip.hpp"
#endif

namespace strx {
#pragma region specialized formatter tokens
	const struct __endf {} endf;
	const struct __endfclr {} endfclr;
#pragma endregion


#pragma region namespace level methods
	/// <summary>
	/// Generates a specialized string representation of the provided value <paramref name="arg"/>.
	/// </summary>
	/// <param name="fmt">The specialized format the value is to be formatted to. (i.e "%#.2f")</param>
	/// <param name="arg">The value to be formatted into the resulting string.</param>
	/// <param name="buff_size">The size of buffer to use for the underlying <seealso cref="snprintf"/> call.</param>
	/// <returns>The formatted string.</returns>
	template<typename T>
	::std::string_view spec(const char * fmt, const T &arg, const size_t &buff_size = 32) {
		::std::string buff;
		buff.resize(buff_size + 1);
		int written = snprintf(const_cast<char*>(buff.data()), buff.size(), fmt, arg);
		buff = buff.substr(0, written);
		return buff;
	}
#pragma endregion


	/// <summary>
	/// Formatter for <seealso cref="::std::string"/> which provides simplified string formatting
	/// </summary>
	/// <example>
	/// // Simple
	/// string str = "{0} {1}"_f
	///     % "Hello"
	///     % "World"
	///     % format::end;
	/// // Custom
	/// string str = "Average {0}"_f
	///     % format::spec("%#.3f", (1.0 + 2.3 + 4.7) / 3)
	///     % format::end;
	/// </example>
	class format
	{
#pragma region instance variables
	private:
		::std::string _fmt;
		::std::string _val;
		::std::vector<::std::string> _params;
#pragma endregion


#pragma region constructors
	public:
		/// <summary>
		/// Constructs the formatter using the provided <paramref name="format"/> string.
		/// </summary>
		/// <param name="format">Format string</param>
		format(const ::std::string_view &format) : _fmt(format) {}
		format(const char *format) : _fmt(format) {}
#pragma endregion


	private:
		inline format& set_param(const ::std::string_view &&param) {
			dirty();
			_params.push_back(param);
			return *this;
		}
		inline bool is_dirty() const { return _val.empty(); }
		inline void dirty() { _val = ""; }


#pragma region operator overloads
	public:
		inline ::std::string_view &operator[](const size_t &index) { return _params[index]; }
		inline const ::std::string_view &operator[](const size_t &index) const { return _params[index]; }

#ifdef string_view
		inline format& operator%(const char &c) { return set_param(::std::string_view(1, c)); }
#else
		inline format& operator%(const char &c) { return set_param(::std::string_view(&c, 1)); }
#endif
		inline format& operator%(const int16_t &s) { return set_param(spec("%hd", s, 6)); }
		inline format& operator%(const uint16_t &s) { return set_param(spec("%hu", s, 6)); }
		inline format& operator%(const int32_t &i) { return set_param(spec("%d", i, 11)); }
		inline format& operator%(const uint32_t &i) { return set_param(spec("%du", i, 11)); }
		inline format& operator%(const int64_t &l) { return set_param(spec("%ll", l, 20)); }
		inline format& operator%(const uint64_t &l) { return set_param(spec("%llu", l, 21)); }
		inline format& operator%(const float &f) { return set_param(spec("%f", f, 30)); }
		inline format& operator%(const double &d) { return set_param(spec("%f", d, 30)); }
		inline format& operator%(const char* c_str) { return set_param(c_str); }
#ifdef string_view
		inline format& operator%(const ::std::string &str) { return set_param(str.c_str()); }
#else
		inline format& operator%(const ::std::string_view &str) { return set_param(str.data()); }
#endif
		inline ::std::string operator%(const __endf &e) { return this->str(); }
		inline ::std::string operator%(const __endfclr &e) { return this->strclr(); }
		inline format& operator+=(const char *c_str) { _fmt += c_str; return *this; }
#ifdef string_view
		inline format& operator+=(const ::std::string &str) { _fmt += str; return *this; }
#else
		inline format& operator+=(const ::std::string_view &str) { _fmt += str.data(); return *this; }
#endif
#pragma endregion


#pragma region public methods
	public:
		/// <summary>
		/// Provides the number of parameters which have been provided so far.
		/// </summary>
		/// <returns>Number of parameters provided so far.</returns>
		inline size_t count() { return _params.size(); }
		/// <summary>
		/// Appends the provided string onto the end of the argument list.
		/// </summary>
		/// <param name="arg">string to be added to list.</param>
		inline void append(const ::std::string &arg) { dirty(); _params.push_back(arg); }
		/// <summary>
		/// Inserts the provided string into the provided index of the argument list.
		/// </summary>
		/// <param name="arg">string to be inserted in the list</param>
		inline void insert(const size_t &index, const ::std::string &arg) { dirty(); _params.insert(_params.begin() + index, arg); }
		/// <summary>
		/// Replaces the formatted string parameter at the given index in the parameter list.
		/// </summary>
		/// <param name="index">Index of parameter to be replaced.</param>
		/// <param name="arg">New value that is to replace the old value.</param>
		inline void replace(size_t index, ::std::string arg) { dirty(); _params[index] = arg; }
		/// <summary>
		/// Clears all parameters provided up until now.
		/// </summary>
		inline void clear() { dirty(); _params.clear(); }
		/// <summary>
		/// Builds the formatted string using the previously provided parameters.
		/// </summary>
		/// <returns>Formatted string.</returns>
		::std::string str();
		/// <summary>
		/// Builds the formatted string using the previously provided parameters, then clears the parameters.
		/// </summary>
		/// <returns>Formatted string.</returns>
		::std::string strclr();
#pragma endregion
	};

#pragma region Formatter User Defined Literals
	/// <summary>
	/// Instantiates a string formatter using the provided string literal.
	/// </summary>
	/// <param name="c_str">String literal to use.</param>
	/// <param name="length">Length of the string literal.</param>
	/// <returns>Format object using the string literal.</returns>
	inline format operator "" _f(const char *c_str, size_t length) { return ::std::move(format(::std::string(::std::move(c_str), ::std::move(length)))); }
#pragma endregion


#pragma region Global Operator Overloads
	/// <summary>
	/// Prints out the formatted string to the provided <seealso cref="::std::ostream"/>
	/// so a formatter can be used within a standard output stream chain.
	/// </summary>
	/// <param name="out">Output stream for printing.</param>
	/// <param name="fmt">Format object to be printed to the output stream.</param>
	/// <returns>The original output stream.</returns>
	inline ::std::ostream& operator<<(::std::ostream& out, format& fmt) { return out << fmt.str(); }
	inline format operator%(const ::std::string &str, const char &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const int16_t &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const uint16_t &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const int32_t &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const uint32_t &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const int64_t &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const uint64_t &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const float &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const double &val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const char* val) { return format(str) % val; }
	inline format operator%(const ::std::string &str, const ::std::string &val) { return format(str) % val; }
#pragma endregion
}

#endif