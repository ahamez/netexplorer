cmake_minimum_required(VERSION 2.8.9)

#--------------------------------------------------------------------------------------------------#

project (netexplorer)

#--------------------------------------------------------------------------------------------------#

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX14)
if(NOT COMPILER_SUPPORTS_CXX14)
  message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif ()

#--------------------------------------------------------------------------------------------------#

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.56.0 REQUIRED COMPONENTS system thread filesystem regex date_time)

if (NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
endif ()

message("-- Boost Include: ${Boost_INCLUDE_DIR}")
message("-- Boost Libraries: ${Boost_LIBRARY_DIRS}")

#--------------------------------------------------------------------------------------------------#

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_definitions("-Wall")
add_definitions("-std=c++1y")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_definitions("-stdlib=libc++")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -std=c++1y -stdlib=libc++")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

#--------------------------------------------------------------------------------------------------#

find_package(cppnetlib 0.11.0 REQUIRED)

#--------------------------------------------------------------------------------------------------#

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${Boost_INCLUDE_DIRS}")
include_directories(${CPPNETLIB_INCLUDE_DIRS})

#--------------------------------------------------------------------------------------------------#

add_subdirectory(ntx)
