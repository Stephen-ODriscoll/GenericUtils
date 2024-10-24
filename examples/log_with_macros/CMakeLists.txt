#
# Copyright (c) 2024 Stephen O Driscoll
#
# Distributed under the MIT License (See accompanying file LICENSE)
# Official repository: https://github.com/Stephen-ODriscoll/PlutoUtils
#

project(log_with_macros)

include_directories(
    ../../include)

add_executable(
    ${PROJECT_NAME}
    log_with_macros.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "examples")
