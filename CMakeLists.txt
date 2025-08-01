cmake_minimum_required(VERSION 3.15)

project(ZeldaClone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(glad CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(engine)
add_executable(ZeldaClone src/main.cpp)
target_link_libraries(ZeldaClone
        PRIVATE
        ${SDL2_LIBRARIES}
        glad::glad
        engine
        OpenGL::GL
)