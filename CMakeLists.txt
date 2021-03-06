cmake_minimum_required(VERSION 3.8)
project(hygge)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)

if (WIN32)
  find_package(SDL2 REQUIRED)
else()
  find_package(SDL2 REQUIRED)
  add_executable(hygge main.cpp
    scene.cpp
    player.cpp
    pupper.cpp
    minion.cpp
    patrolling_minion.cpp
    mover.cpp
    moverpup.cpp

    tutorial_scene.cpp
    home_scene.cpp
    platforming_scene.cpp
    you_died.cpp
    )

  target_link_libraries(hygge PRIVATE ${SDL2_LIBRARY})
  target_include_directories(hygge SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})
  target_compile_definitions(hygge PUBLIC -DNONWINDOWS_BUILD)
endif()
