/*
* Copyright (c) 2024 Stephen O Driscoll
*
* Distributed under the MIT License (See accompanying file LICENSE)
* Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
*/

#pragma once

#ifndef PLUTO_FILESYSTEM_IS_EXPERIMENTAL
#if (defined(__cplusplus) && __cplusplus > 201402L) || (defined(_MSVC_LANG) && _MSVC_LANG > 201402L)
#define PLUTO_FILESYSTEM_IS_EXPERIMENTAL 0
#else
#define PLUTO_FILESYSTEM_IS_EXPERIMENTAL 1
#if (defined(_MSVC_LANG) && !defined(_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING))
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#endif
#endif

#if PLUTO_FILESYSTEM_IS_EXPERIMENTAL
#include <experimental/filesystem>
#else
#include <filesystem>
#endif

namespace pluto
{
#if PLUTO_FILESYSTEM_IS_EXPERIMENTAL
    namespace FileSystem = std::experimental::filesystem;
#else
    namespace FileSystem = std::filesystem;
#endif
}
