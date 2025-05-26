cmake_minimum_required(VERSION 3.23)

set(project "menu")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES menu.cpp)

set(${project}_HEADERS menu.h)

set(${project}_SOURCE_LIST ${${project}_SOURCES} ${${project}_HEADERS})

add_library(${project} STATIC ${${project}_SOURCE_LIST})

target_link_libraries(${project} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
