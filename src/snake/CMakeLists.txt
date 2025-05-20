cmake_minimum_required(VERSION 3.23)

set(project "snake")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES orientation.cpp foodSpawner.cpp game.cpp field.cpp segment.cpp snake.cpp)

set(${project}_HEADERS orientation.h foodSpawner.h game.h field.h segment.h snake.h)

set(${project}_SOURCE_LIST ${${project}_SOURCES} ${${project}_HEADERS})

add_library(${project} STATIC ${${project}_SOURCE_LIST})

target_link_libraries(${project} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
