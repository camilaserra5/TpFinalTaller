cmake_minimum_required(VERSION 2.8)

project(editor)

include_directories(${PROJECT_SOURCE_DIR}/include)

# find_package(Qt5 COMPONENTS Widgets Core <...>) es una forma más feliz de
# agregar paquetes, ver https://blog.kitware.com/cmake-finding-qt5-the-right-way/
find_package(Qt5Widgets)
find_package(yaml-cpp)

set ( PROJECT_LINK_LIBS libcommons.a )
link_directories( ~/TpFinalTaller/common_src/build )
include_directories(~/TpFinalTaller/common_src/include )

add_executable(out
  src/editor.cpp
  src/editor_main.cpp
  ${UIS_HEADERS})

# Linkea libQt5Widgets.so al ejecutable
target_link_libraries(out ${PROJECT_LINK_LIBS} Qt5::Widgets ${YAML_CPP_LIBRARIES})
