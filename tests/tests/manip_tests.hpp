#pragma once
#ifndef _MANIP_TESTS_HPP
#define _MANIP_TESTS_HPP

#include "../cpp-test/test_suite.hpp"
#include <stringx.hpp>
#include <memory>

namespace manip_tests {
	namespace split {
		inline void none() {
			auto tokens = strx::split("helloworld", '_');
			ASSERT_FALSE(tokens.size() > 1, "more tokens than expected");
			ASSERT_FALSE(tokens.size() < 1, "less tokens than expected");
			ASSERT_TRUE(tokens[0] == "helloworld", "token invalid");
		}
		inline void single() {
			auto tokens = strx::split("hello_world", '_');
			ASSERT_FALSE(tokens.size() > 2, "more tokens than expected");
			ASSERT_FALSE(tokens.size() < 2, "less tokens than expected");
			ASSERT_TRUE(tokens[0] == "hello", "first token invalid");
			ASSERT_TRUE(tokens[1] == "world", "second token invalid");
		}
		inline void multi() {
			const int TOKEN_COUNT = 10;
			std::string target = "";
			for (int c = 0; c < TOKEN_COUNT; c++) {
				if (c)
					target += '_';
				target += 'a' + c;
			}

			auto tokens = strx::split(target, '_');
			ASSERT_FALSE(tokens.size() > TOKEN_COUNT, "more tokens than expected");
			ASSERT_FALSE(tokens.size() < TOKEN_COUNT, "less tokens than expected");
			for (int c = 0; c < TOKEN_COUNT; c++) {
				std::string comp = "a";
				comp[0] += c;
				ASSERT_TRUE(tokens[c] == comp, ("token '" + comp + "' invalid").data());
			}
		}
		DECLARE_TEST_SET({
			/* Add each test case functions */
			TEST(none);
			TEST(single);
			TEST(multi);
		})
	} // namespace split

	namespace join {
		inline void character() {
			std::vector<std::string> tokens = {"a","b","c","d"};
			auto result = strx::join(tokens, '_');
			ASSERT_TRUE(result == "a_b_c_d", "concatenated string is not in expected state");
		}
		inline void string() {
			std::vector<std::string> tokens = {"a","b","c","d"};
			auto result = strx::join(tokens, "_-_");
			ASSERT_TRUE(result == "a_-_b_-_c_-_d", "concatenated string is not in expected state");
		}
		DECLARE_TEST_SET({
			/* Add each test case functions */
			TEST(character);
			TEST(string);
		})
	}

	namespace replace {
		inline void single_character() {
			auto result = strx::replace("abcabc", 'b', 'e');
			ASSERT_TRUE(result == "aecaec", "replacement result is not in expected state");
			result = strx::replace("abcabc", 'd', 'e');
			ASSERT_TRUE(result == "abcabc", "replacement result is not in expected state");
		}
		inline void string_with_character() {
			auto result = strx::replace("abcabc", "ab", 'e');
			ASSERT_TRUE(result == "ecec", "replacement result is not in expected state");
			// result = strx::replace("abcabc", "db", 'e');
			// ASSERT_TRUE(result == "abcabc", "replacement result is not in expected state");
		}

		DECLARE_TEST_SET({
			/* Add each test case functions */
			TEST(single_character);
			TEST(string_with_character);
		})
	}

} // namespace manip_tests

#endif
