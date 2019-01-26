cmake_minimum_required(VERSION 3.8)
project(hygge)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
  find_package(SDL2 REQUIRED)
else()
  find_package(SDL2 REQUIRED)
  add_executable(hygge main.cpp

    asteroid_scene.cpp
    ship.cpp

    scene.cpp)
  target_link_libraries(hygge PRIVATE SDL2)
  target_compile_definitions(hygge PUBLIC -DNONWINDOWS_BUILD)
endif()
