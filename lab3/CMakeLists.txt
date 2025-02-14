cmake_minimum_required(VERSION 3.10)
project(FigureProject LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file(GLOB SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_library(Figure_lib STATIC ${SRC_FILES})


target_include_directories(Figure_lib
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(Figure_exe
        ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp
)

target_link_libraries(Figure_exe PRIVATE Figure_lib)


enable_testing()

add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/test/tests03.cpp
)
target_link_libraries(tests PRIVATE Figure_lib gtest_main)


add_test(NAME FigureTests COMMAND tests)