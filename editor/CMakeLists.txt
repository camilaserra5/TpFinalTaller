cmake_minimum_required(VERSION 3.5)

project(editor LANGUAGES CXX)
cmake_policy(SET CMP0015 NEW)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_LINK_LIBS commons)
link_directories(../common/build)
include_directories(../common/include)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(yaml-cpp)

file(GLOB SOURCES src/*.cpp include/*.h)
add_executable(editor
        ${SOURCES})

target_link_libraries(editor ${PROJECT_LINK_LIBS} Qt5::Widgets ${YAML_CPP_LIBRARIES})

install(TARGETS editor COMPONENT editor RUNTIME DESTINATION "/usr/local/bin" LIBRARY DESTINATION "/usr/local/bin" DESTINATION "/usr/local/bin")