#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
#

project(GenericUtilsTests)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
endif()

include_directories(
    ../include)

add_executable(
    ${PROJECT_NAME}
    CompareTests.cpp
    ContainerUtilsTests.cpp
    FileSystemTests.cpp
    GenericTests.cpp
    IteratorUtilsTests.cpp
    LocaleTests.cpp
    LogTests.cpp
    LRUCacheTests.cpp
    Main.cpp
    RangeTests.cpp
    SafeLRUCacheTests.cpp
    ScopeExitActionsTests.cpp
    StandardTests.cpp
    StopwatchTests.cpp
    StringUtilsTests.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    gtest)

if((NOT MSVC) AND CMAKE_CXX_STANDARD EQUAL 14)
    target_link_libraries(
        ${PROJECT_NAME}
        stdc++fs)
endif()
