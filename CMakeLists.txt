cmake_minimum_required(VERSION 3.13)

project(Amu VERSION 0.1.0 LANGUAGES C CXX)

# ===-- Core Library ------------------------------------------------------=== #

# Allow developers to configure the path to the WSTP API, which will almost
# always be necessary to build Amu successfully.
option(WSTP_API_PATH "Path to the WSTP API headers & binaries" "NULL")
if(NOT ${WSTP_API_PATH} STREQUAL "NULL")
  include_directories(${WSTP_API_PATH})
  link_directories(${WSTP_API_PATH})
endif()

set(AMU_CORE_SOURCES
  include/amu/Engine.h
  include/amu/Tools.h
  core/Engine.cpp
  core/Tools.cpp)

add_library(AmuCore ${AMU_CORE_SOURCES})
target_include_directories(AmuCore PUBLIC include)
target_compile_features(AmuCore PRIVATE cxx_std_17)
target_link_libraries(AmuCore PRIVATE WSTPi4)

# Link to Foundation on macOS
if(APPLE)
  target_link_libraries(AmuCore PRIVATE "-framework Foundation")
endif()

# ===-- User Interface ----------------------------------------------------=== #

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

qt_add_executable(Amu MANUAL_FINALIZATION ${AMU_SOURCES})
target_link_libraries(Amu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets AmuCore)
target_compile_features(Amu PRIVATE cxx_std_17)
qt_finalize_executable(Amu)
