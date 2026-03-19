file(GLOB TEST_SOURCES "${CMAKE_CURRENT_LIST_DIR}/test_*.cpp")
file(GLOB PROJECT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/../src/*.cpp")

# Excluye main.cpp
list(REMOVE_ITEM PROJECT_SOURCES "${CMAKE_CURRENT_LIST_DIR}/../src/main.cpp")

add_executable(testing ${TEST_SOURCES} ${PROJECT_SOURCES})
target_include_directories(testing PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../include")
target_link_libraries(testing PRIVATE GTest::gtest_main raylib)

if (TEST_SOURCES)
    include(GoogleTest)
    gtest_discover_tests(testing)
endif()