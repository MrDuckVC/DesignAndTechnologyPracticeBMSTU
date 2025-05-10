cmake_minimum_required(VERSION 3.23)

set(project "practice")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(${project}_SOURCES src/main.cpp)

add_subdirectory(src/games)
add_subdirectory(src/chess)
add_subdirectory(src/menu)

set(${project}_SOURCE_LIST ${${project}_SOURCES})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${project} ${${project}_SOURCE_LIST})

target_compile_features(${project} PRIVATE cxx_std_17)
target_link_libraries(${project} PRIVATE SFML::Graphics)
target_link_libraries(${project} PRIVATE SFML::Audio)

target_link_libraries(${project} PRIVATE menu games chess)

if(ENABLE_DEBUG)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
endif()
