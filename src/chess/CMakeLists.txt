cmake_minimum_required(VERSION 3.23)

set(project "chess")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES chess.cpp)

set(${project}_HEADERS chess.h)

set(${project}_SOURCE_LIST ${${project}_SOURCES} ${${project}_HEADERS})

# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/chessLogo.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_library(${project} STATIC ${${project}_SOURCE_LIST})

target_link_libraries(${project} PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)
