cmake_minimum_required(VERSION 2.8)

project(raycasting)
find_package(Threads REQUIRED)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -lm")

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})
#find_package(yaml-cpp)

set ( PROJECT_LINK_LIBS libcommons.a )
link_directories( ~/TpFinalTaller/common_src/build )
include_directories(~/TpFinalTaller/common_src/include )

add_executable (raycast
        ../raycast.cpp
        ../common_src/include/map.h
        ../common_src/src/map.cpp
        ../rayo.cpp
        ${UIS_HEADERS})

#target_link_libraries(raycasting ${PROJECT_LINK_LIBS} SDL2 SDL2_image Threads::Threads ${YAML_CPP_LIBRARIES})
