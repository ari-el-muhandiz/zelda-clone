cmake_minimum_required(VERSION 3.15)

project(ZeldaClone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add vcpkg installed directory to CMake search path
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg_installed/arm64-osx")

find_package(SDL3 REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EnTT CONFIG REQUIRED)

add_subdirectory(engine)
add_executable(ZeldaClone src/main.cpp)

target_link_libraries(ZeldaClone
        PRIVATE
        engine
)
