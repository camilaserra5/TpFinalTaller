cmake_minimum_required(VERSION 3.5)

project(editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_LINK_LIBS libcommons.a)
link_directories(~/TpFinalTaller/common_src/build)
include_directories(~/TpFinalTaller/common_src/include)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(yaml-cpp)

add_executable(editor
        src/editor_main.cpp
        src/mainwindow.cpp
        include/mainwindow.h
        src/map_tiles_list.cpp
        include/map_tiles_list.h
        src/map_widget.cpp
        include/map_widget.h
        )

target_link_libraries(editor ${PROJECT_LINK_LIBS} Qt5::Widgets ${YAML_CPP_LIBRARIES})
