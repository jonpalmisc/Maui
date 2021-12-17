cmake_minimum_required(VERSION 3.13)

project(amu VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(AMU_SOURCES
  ui/Cell.h
  ui/Cell.cpp
  ui/Main.cpp
  ui/MainWindow.cpp
  ui/MainWindow.h
  ui/Theme.h
  ui/Theme.cpp
)

qt_add_executable(amu MANUAL_FINALIZATION ${AMU_SOURCES})
target_link_libraries(amu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_features(amu PRIVATE cxx_std_17)
qt_finalize_executable(amu)
