# engine/CMakeLists.txt

add_library(engine input/InputManager.cpp)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/input)