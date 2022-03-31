cmake_minimum_required(VERSION 3.13)

project(Maui VERSION 0.1.0 LANGUAGES C CXX)

# ===-- Core Library ------------------------------------------------------=== #

# Allow developers to configure the path to the WSTP API, which will almost
# always be necessary to build Maui successfully.
option(WSTP_API_PATH "Path to the WSTP API headers & binaries" "NULL")

if (APPLE)
  find_library(WSTP NAMES wstp PATHS ${WSTP_API_PATH} REQUIRED)
  include_directories(${WSTP}/Headers)
elseif (WIN32)
#  On Windows, we should set WSTP_API_PATH to:
#  C:\Program Files\Wolfram Research\Wolfram Engine\13.0\SystemFiles\Links\WSTP\DeveloperKit\Windows-x86-64
  find_library(WSTP NAMES wstp64i4 PATHS ${WSTP_API_PATH}/CompilerAdditions REQUIRED)
  include_directories(${WSTP_API_PATH}/CompilerAdditions)
else()
#  TODO: other platforms
endif()

set(MAUI_CORE_SOURCES
  include/maui/Engine.h
  include/maui/Tools.h
  core/Engine.cpp
  core/Tools.cpp)

add_library(MauiCore ${MAUI_CORE_SOURCES})
target_include_directories(MauiCore PUBLIC include)
target_compile_features(MauiCore PRIVATE cxx_std_17)
target_link_libraries(MauiCore PRIVATE ${WSTP})

# Link to Foundation on macOS
if(APPLE)
  target_link_libraries(MauiCore PRIVATE "-framework Foundation")
endif()

if (WIN32)
  add_custom_command(TARGET MauiCore POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "copying wstp64i4.dll"
    COMMAND ${CMAKE_COMMAND} -E copy ${WSTP_API_PATH}/SystemAdditions/wstp64i4.dll ${CMAKE_BINARY_DIR}
    )
endif()

# ===-- User Interface ----------------------------------------------------=== #

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(MAUI_SOURCES
  ui/Cell.h
  ui/Cell.cpp
  ui/ConfigDialog.h
  ui/ConfigDialog.cpp
  ui/Main.cpp
  ui/MainWindow.h
  ui/MainWindow.cpp
  ui/Theme.h
  ui/Theme.cpp
)

if (APPLE)
  qt_add_executable(Maui MANUAL_FINALIZATION MACOSX_BUNDLE ${MAUI_SOURCES})
else()
  qt_add_executable(Maui MANUAL_FINALIZATION ${MAUI_SOURCES})

endif()
qt_add_resources(Maui "fonts"
  PREFIX "/"
  FILES ui/fonts/Ubuntu-Regular.ttf ui/fonts/UbuntuMono-Regular.ttf)
target_link_libraries(Maui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets MauiCore)
target_compile_features(Maui PRIVATE cxx_std_17)
qt_finalize_executable(Maui)

# ===-- Formatting --------------------------------------------------------=== #

add_custom_target(format
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND clang-format -i --style=WebKit ${MAUI_CORE_SOURCES} ${MAUI_SOURCES})
