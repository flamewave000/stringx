#pragma once
#ifndef _SEARCH_TESTS_HPP
#define _SEARCH_TESTS_HPP

#include "../cpp-test/test_suite.hpp"
#include <stringx.hpp>

namespace search_tests {
namespace contains {
inline void character() {
	ASSERT_TRUE(strx::contains("abcdefg", 'a'), "string does not contain character 'a'");
	ASSERT_TRUE(strx::contains("abcdefg", 'e'), "string does not contain character 'e'");
	ASSERT_TRUE(strx::contains("abcdefg", 'g'), "string does not contain character 'g'");
}
inline void text() {
	ASSERT_TRUE(strx::contains("abcdefg", "abc"), "string does not contain string 'abc'");
	ASSERT_TRUE(strx::contains("abcdefg", "cde"), "string does not contain string 'cde'");
	ASSERT_TRUE(strx::contains("abcdefg", "efg"), "string does not contain string 'efg'");
}
inline void not_character() {
	ASSERT_FALSE(strx::contains("abcdefg", 'x'), "string contains character 'x'");
	ASSERT_FALSE(strx::contains("abcdefg", 'y'), "string contains character 'y'");
	ASSERT_FALSE(strx::contains("abcdefg", 'z'), "string contains character 'z'");
}
inline void not_text() {
	ASSERT_FALSE(strx::contains("abcdefg", "acb"), "string contains string 'acb'");
	ASSERT_FALSE(strx::contains("abcdefg", "ced"), "string contains string 'ced'");
	ASSERT_FALSE(strx::contains("abcdefg", "egf"), "string contains string 'egf'");
}
DECLARE_TEST_SET({
	/* Add each test case functions */
	TEST(character);
	TEST(text);
	TEST(not_character);
	TEST(not_text);
})
} // namespace contains

namespace starts_with {
inline void text() {
	ASSERT_TRUE(strx::starts_with("abcdefg", "abc"), "string does not start with string 'abc'");
}
inline void not_text() {
	ASSERT_FALSE(strx::starts_with("abcdefg", "efg"), "string starts with string 'efg'");
}
DECLARE_TEST_SET({
	/* Add each test case functions */
	TEST(text);
	TEST(not_text);
})
} // namespace starts_with
} // namespace search_tests

#endif
