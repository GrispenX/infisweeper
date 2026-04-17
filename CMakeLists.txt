cmake_minimum_required(VERSION 3.16)
project(Infisweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

set(SOURCES)
set(GAME_SOURCES)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)