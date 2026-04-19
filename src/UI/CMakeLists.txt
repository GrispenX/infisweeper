list(APPEND SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/AssetManager.cpp
)

add_subdirectory(MainMenuScreen)
add_subdirectory(NewGameScreen)
add_subdirectory(LoadGameScreen)
add_subdirectory(GameScreen)

set(SOURCES ${SOURCES} PARENT_SCOPE)