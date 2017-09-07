#ifndef _STRINGX_
#define _STRINGX_

#ifdef _MSVC_LANG
#if _MSVC_LANG < 201402L
#error Requires C++14 or higher to compile
#elif _MSVC_LANG == 201402L
#define string_view string
#endif
#elif __cplusplus < 201402L
#error Requires C++14 or higher to compile
#elif __cplusplus == 201402L
#define string_view string
#endif

#ifndef _STRX_FORMAT_H
#include "strx_format.hpp"
#endif

#ifdef string_view
#undef string_view
#endif

#endif