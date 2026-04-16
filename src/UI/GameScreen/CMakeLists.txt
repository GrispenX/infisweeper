add_library(GameScreen_lib
    GameScreen.cpp
    GameView.cpp
    PlainPosition.cpp
)

target_include_directories(GameScreen_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)