#pragma once
#ifndef _TESTS_HPP
#define _TESTS_HPP

#include "cpp-test/test_suite.hpp"

/* Include test headers here */
#include "tests/search_tests.hpp"
#include "tests/manip_tests.hpp"
/*****************************/


DECLARE_RUN_SET(strx_manip_run_set, {
/* Add the test sets to be run here */
	RUN(::search_tests::contains);
	RUN(::search_tests::starts_with);
	RUN(::manip_tests::split);
	RUN(::manip_tests::join);
	RUN(::manip_tests::replace);
/************************************/
})

#endif
