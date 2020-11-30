project(wolfstein)

# Busca el módulo Widgets de la biblioteca Qt5
# en particular toma la configuración de /usr/lib/x86_64-linux-gnu/cmake/Qt5/Qt5WidgetsConfig.cmake

include_directories(${PROJECT_SOURCE_DIR}/include)

# find_package(Qt5 COMPONENTS Widgets Core <...>) es una forma más feliz de
# agregar paquetes, ver https://blog.kitware.com/cmake-finding-qt5-the-right-way/
find_package(Qt5Widgets)

add_executable(out
  src/editor.cpp
  src/editor_main.cpp
  ${UIS_HEADERS})

# Linkea libQt5Widgets.so al ejecutable
target_link_libraries(out Qt5::Widgets)
