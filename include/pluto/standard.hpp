/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

// C++ 11
#if (defined(__cplusplus) && __cplusplus > 199711L) || (defined(_MSVC_LANG) && _MSVC_LANG > 199711L)
#include <array>
#include <atomic>
#include <cfenv>
#include <chrono>
#include <cinttypes>
#include <condition_variable>
#include <cstdint>
#include <cuchar>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#endif

// C++ 14
#if (defined(__cplusplus) && __cplusplus > 201103L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201103L)
#include <shared_mutex>
#endif

// C++ 17
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
#if __has_include(<any>)
#include <any>
#endif
#if __has_include(<charconv>)
#include <charconv>
#endif
#if __has_include(<execution>)
#include <execution>
#endif
#if __has_include(<filesystem>)
#include <filesystem>
#endif
#if __has_include(<memory_resource>)
#include <memory_resource>
#endif
#if __has_include(<optional>)
#include <optional>
#endif
#if __has_include(<string_view>)
#include <string_view>
#endif
#if __has_include(<variant>)
#include <variant>
#endif
#else
#include <ccomplex>
#include <codecvt>
#include <cstdalign>
#include <cstdbool>
#include <ctgmath>
#endif

// C++ 20
#if (defined(__cplusplus) && __cplusplus > 201703L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201703L)
#if __has_include(<barrier>)
#include <barrier>
#endif
#if __has_include(<bit>)
#include <bit>
#endif
#if __has_include(<compare>)
#include <compare>
#endif
#if __has_include(<concepts>)
#include <concepts>
#endif
#if __has_include(<coroutine>)
#include <coroutine>
#endif
#if __has_include(<format>)
#include <format>
#endif
#if __has_include(<latch>)
#include <latch>
#endif
#if __has_include(<numbers>)
#include <numbers>
#endif
#if __has_include(<ranges>)
#include <ranges>
#endif
#if __has_include(<semaphore>)
#include <semaphore>
#endif
#if __has_include(<source_location>)
#include <source_location>
#endif
#if __has_include(<span>)
#include <span>
#endif
#if __has_include(<stop_token>)
#include <stop_token>
#endif
#if __has_include(<syncstream>)
#include <syncstream>
#endif
#if __has_include(<version>)
#include <version>
#endif
#else
#include <ciso646>
#endif

// C++ 23
#if (defined(__cplusplus) && __cplusplus > 202002L) || (defined(_MSVC_LANG) && _MSVC_LANG > 202002L)
#if __has_include(<expected>)
#include <expected>
#endif
#if __has_include(<flat_map>)
#include <flat_map>
#endif
#if __has_include(<flat_set>)
#include <flat_set>
#endif
#if __has_include(<generator>)
#include <generator>
#endif
#if __has_include(<mdspan>)
#include <mdspan>
#endif
#if __has_include(<print>)
#include <print>
#endif
#if __has_include(<spanstream>)
#include <spanstream>
#endif
#if __has_include(<stacktrace>)
#include <stacktrace>
#endif
#if __has_include(<stdfloat>)
#include <stdfloat>
#endif
#endif

// C++ 26 (when available)
#if (defined(__cplusplus) && __cplusplus > 202302L) || (defined(_MSVC_LANG) && _MSVC_LANG > 202302L)
#if __has_include(<debugging>)
#include <debugging>
#endif
#if __has_include(<hazard_pointer>)
#include <hazard_pointer>
#endif
#if __has_include(<inplace_vector>)
#include <inplace_vector>
#endif
#if __has_include(<linalg>)
#include <linalg>
#endif
#if __has_include(<rcu>)
#include <rcu>
#endif
#if __has_include(<text_encoding>)
#include <text_encoding>
#endif
#endif
