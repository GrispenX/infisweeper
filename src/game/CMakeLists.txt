add_library(game_lib
    Geometries.cpp
    Cell.cpp
    # Chunk.cpp
)

target_include_directories(game_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)