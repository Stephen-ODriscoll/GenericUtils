/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
*/

#pragma once

#ifndef GENERIC_FILESYSTEM_IS_EXPERIMENTAL
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
#define GENERIC_FILESYSTEM_IS_EXPERIMENTAL 0
#else
#define GENERIC_FILESYSTEM_IS_EXPERIMENTAL 1
#if (defined(_MSVC_LANG) && !defined(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING))
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#endif
#endif

#if GENERIC_FILESYSTEM_IS_EXPERIMENTAL
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

namespace Generic
{
#if GENERIC_FILESYSTEM_IS_EXPERIMENTAL
    namespace filesystem = std::experimental::filesystem;
#else
    namespace filesystem = std::filesystem;
#endif
}
