#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
#

project(generic_utils)

add_library(
    ${PROJECT_NAME}
    INTERFACE
    generic.hpp
    generic/compare.hpp
    generic/container_utils.hpp
    generic/filesystem.hpp
    generic/iterator_utils.hpp
    generic/locale.hpp
    generic/log.hpp
    generic/lru_cache.hpp
    generic/range.hpp
    generic/safe_lru_cache.hpp
    generic/Scope_exit_actions.hpp
    generic/standard.hpp
    generic/stopwatch.hpp
    generic/string_utils.hpp)
