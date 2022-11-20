// copyright (c) 2020 by Chrono

#ifndef __CPP_LANG_HPP__ // Include Guard
#define __CPP_LANG_HPP__ // Include Guard

#include <cassert> // C++ stadnard library

#include <iostream> // C++ stadnard library

#include <string> // C++ stadnard library

#include <vector> // C++ stadnard library

#include <set> // C++ stadnard library

#include <map> // C++ stadnard library

#include <algorithm> // C++ stadnard library

#include <unordered_map> // C++ stadnard library

#include <regex>

#include <atomic>

#include <future>

#include <thread>


// you have to use c++11 or later 

#if __cplusplus <201103
#   error "need c++11 or later"
#endif // __cplusplus < 201103

//[[deprecated]]

#if __cplusplus >= 201402
#   define CPP_DEPRECATED [[deprecated]]
#else
#   define CPP_DEPRECATED [[gnu::deprecated]]


// static assert

#if __cpp__static_assert >= 201411
#define STATIC_ASSERT(x) static_assert(x)
#else
#define STATIC_ASSERT(x) static_assert(x, #x)
#   endif // __cpp__static_assert >= 201411

// macro for convinent namespace
#define BEGIN_NAMESPACE(x) namespace x {
#define END_NAMESPACE(x) }
#define USING_NAMESPACE(x) using namespace x;

#endif // __CPP_LANG_HPP__ //Include Guard