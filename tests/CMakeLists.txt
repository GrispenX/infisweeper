find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}Tests
    ${CMAKE_CURRENT_SOURCE_DIR}/CellTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChunkTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameModelTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GeometriesTest.cpp
    ${GAME_SOURCES}
)

target_include_directories(${PROJECT_NAME}Tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}Tests PRIVATE GTest::gtest_main GTest::gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}Tests)
