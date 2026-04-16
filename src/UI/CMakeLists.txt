add_subdirectory(GameScreen)

add_library(UI_lib
    AssetManager.cpp
)

target_link_libraries(UI_lib
    GameScreen_lib
)

target_include_directories(UI_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)