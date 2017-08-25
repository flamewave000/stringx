#ifndef _STRX_FORMAT_H
#define _STRX_FORMAT_H

#ifndef _STRX_MANIP_H
#include "strx_manip.hpp"
#endif

#include <vector>

namespace strx {
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
#pragma region internal classes
	private:
		struct __end {};
		struct __endclr {};
#pragma endregion


#pragma region class variables
	public:
		/// <summary>
		/// Signifies the end of a string format. Will cause the formatter to return a string at the end.
		/// </summary>
		static __end end;
		/// <summary>
		/// Signifies the end of a string format. Will cause the formatter to return a string at the end, then clear the provided parameters.
		/// </summary>
		static __endclr endclr;
#pragma endregion


#pragma region instance variables
	private:
		::std::string _buffer;
		::std::vector<::std::string> _params;
#pragma endregion


#pragma region constructors
	public:
		/// <summary>
		/// Constructs the formatter using the provided <paramref name="format"/> string.
		/// </summary>
		/// <param name="format">Format string</param>
		format(const ::std::string &format) : _buffer(format) {}
		format(const char *format) : _buffer(format) {}
#pragma endregion


#pragma region operator overloads
	public:
		inline ::std::string &operator[](const size_t &index) {
			return _params[index];
		}
		inline const ::std::string &operator[](const size_t &index) const {
			return _params[index];
		}
		inline format& operator%(const char &c) {
			_params.push_back(::std::string(1, c));
			return *this;
		}
		inline format& operator%(const int16_t &s) {
			_params.push_back(spec("%hd", s, 6));
			return *this;
		}
		inline format& operator%(const uint16_t &s) {
			_params.push_back(spec("%hu", s, 6));
			return *this;
		}
		inline format& operator%(const int32_t &i) {
			_params.push_back(spec("%d", i, 11));
			return *this;
		}
		inline format& operator%(const uint32_t &i) {
			_params.push_back(spec("%du", i, 11));
			return *this;
		}
		inline format& operator%(const int64_t &l) {
			_params.push_back(spec("%ll", l, 20));
			return *this;
		}
		inline format& operator%(const uint64_t &l) {
			_params.push_back(spec("%llu", l, 21));
			return *this;
		}
		inline format& operator%(const float &f) {
			_params.push_back(spec("%f", f, 30));
			return *this;
		}
		inline format& operator%(const double &d) {
			_params.push_back(spec("%f", d, 30));
			return *this;
		}
		inline format& operator%(const char* c_str) {
			_params.push_back(c_str);
			return *this;
		}
		inline format& operator%(const ::std::string &str) {
			_params.push_back(str);
			return *this;
		}
		inline ::std::string operator%(const __end &e) const {
			return this->str();
		}
		inline ::std::string operator%(const __endclr &e) {
			return this->strclr();
		}
#pragma endregion


#pragma region public methods
	public:
		/// <summary>
		/// Provides the number of parameters which have been provided so far.
		/// </summary>
		/// <returns>Number of parameters provided so far.</returns>
		inline size_t count() {
			return _params.size();
		}
		/// <summary>
		/// Appends the provided string onto the end of the argument list.
		/// </summary>
		/// <param name="arg">string to be added to list.</param>
		inline void append(const ::std::string &arg) {
			_params.push_back(arg);
		}
		/// <summary>
		/// Inserts the provided string into the provided index of the argument list.
		/// </summary>
		/// <param name="arg">string to be inserted in the list</param>
		inline void insert(const size_t &index, const ::std::string &arg) {
			_params.insert(_params.begin() + index, arg);
		}
		/// <summary>
		/// Replaces the formatted string parameter at the given index in the parameter list.
		/// </summary>
		/// <param name="index">Index of parameter to be replaced.</param>
		/// <param name="arg">New value that is to replace the old value.</param>
		inline void replace(size_t index, ::std::string arg) {
			_params[index] = arg;
		}
		/// <summary>
		/// Clears all parameters provided up until now.
		/// </summary>
		inline void clear() {
			_params.clear();
		}
		/// <summary>
		/// Builds the formatted string using the previously provided parameters.
		/// </summary>
		/// <returns>Formatted string.</returns>
		::std::string str() const;
		/// <summary>
		/// Builds the formatted string using the previously provided parameters, then clears the parameters.
		/// </summary>
		/// <returns>Formatted string.</returns>
		::std::string strclr();
		/// <summary>
		/// Generates a specialized string representation of the provided value <paramref name="arg"/>.
		/// </summary>
		/// <param name="fmt">The specialized format the value is to be formatted to. (i.e "%#.2f")</param>
		/// <param name="arg">The value to be formatted into the resulting string.</param>
		/// <param name="buff_size">The size of buffer to use for the underlying <seealso cref="snprintf"/> call.</param>
		/// <returns>The formatted string.</returns>
		template<typename T>
		static ::std::string spec(const char * fmt, const T &arg, const size_t &buff_size = 32) {
			::std::string buff;
			buff.resize(buff_size + 1);
			int written = snprintf(const_cast<char*>(buff.data()), buff.size(), fmt, arg);
			buff = buff.substr(0, written);
			return buff;
		}
#pragma endregion
	};

#pragma region Formatter User Defined Literals
	inline format operator "" _f(const char *c_str, size_t length) { return ::std::move(format(::std::string(::std::move(c_str), ::std::move(length)))); }
#pragma endregion


#pragma region Global Operator Overloads
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