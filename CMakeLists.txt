cmake_minimum_required(VERSION 3.24.1)

project(ctjs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-deprecated-declarations)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS *.cc)
list(FILTER SOURCES EXCLUDE REGEX \.test\.cc$)

add_executable(ctjs ${SOURCES})
target_include_directories(ctjs PRIVATE ${CMAKE_SOURCE_DIR}/ctjs)

add_subdirectory(tests)