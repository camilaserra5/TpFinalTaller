cmake_minimum_required(VERSION 2.8.11)
if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
project(wolfestein VERSION 1.0.1)

find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

set(PROJECT_BASE_DIR ${PROJECT_SOURCE_DIR})
configure_file(config.h.in config.h)

set(CPACK_COMPONENTS_GROUPING IGNORE)
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "7542")
INCLUDE(CPack)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(common/include)

add_subdirectory(common)
#add_subdirectory(editor)
add_subdirectory(server)
add_subdirectory(client)
