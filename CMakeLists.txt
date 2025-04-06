cmake_minimum_required(VERSION 3.23)

set(project "practice")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES main.cpp)

add_subdirectory(games)
add_subdirectory(chess)

set(${project}_SOURCE_LIST ${${project}_SOURCES})

add_executable(${project} ${${project}_SOURCE_LIST})

target_link_libraries(${project} games chess)

if(ENABLE_DEBUG)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
endif()
