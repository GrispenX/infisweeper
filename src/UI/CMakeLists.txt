add_library(UI_lib
    GameScreen.cpp
    GameView.cpp
    AssetManager.cpp
    PlainPosition.cpp
)

target_include_directories(UI_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)