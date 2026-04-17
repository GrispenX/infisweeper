list(APPEND SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_subdirectory(game)
add_subdirectory(UI)

set(SOURCES ${SOURCES} PARENT_SCOPE)