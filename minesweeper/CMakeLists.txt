cmake_minimum_required(VERSION 3.23)

set(project "mineswepeer")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES mineswepeer.cpp)

set(${project}_HEADERS mineswepeer.h)

set(${project}_SOURCE_LIST ${${project}_SOURCES} ${${project}_HEADERS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mineswepeerLogo.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_library(${project} STATIC ${${project}_SOURCE_LIST})
