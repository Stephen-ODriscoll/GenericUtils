#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

project(pluto_utils_tests)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
endif()

include_directories(
    ../include)

add_executable(
    ${PROJECT_NAME}
    compare_tests.cpp
    container_utils_tests.cpp
    filesystem_tests.cpp
    pluto_tests.cpp
    iterator_utils_tests.cpp
    locale_tests.cpp
    logger_tests.cpp
    lru_cache_tests.cpp
    main.cpp
    range_tests.cpp
    safe_lru_cache_tests.cpp
    scope_exit_actions_tests.cpp
    standard_tests.cpp
    stopwatch_tests.cpp
    string_utils_tests.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    gtest)

if((NOT MSVC) AND CMAKE_CXX_STANDARD EQUAL 14)
    target_link_libraries(
        ${PROJECT_NAME}
        stdc++fs)
endif()
