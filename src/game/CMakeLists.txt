add_library(game_lib
    Cell.cpp
    Chunk.cpp
    ChunkBuilder.cpp
)

target_include_directories(game_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)