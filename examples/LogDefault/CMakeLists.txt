#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/GenericUtils
#

project(LogDefault)

include_directories(
    ../../include)

add_executable(
    ${PROJECT_NAME}
    LogDefault.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "examples")
