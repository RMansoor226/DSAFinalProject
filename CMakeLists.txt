cmake_minimum_required(VERSION 3.31)
project(MovieRecommender)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# Fetch Catch2 v3
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.3
)

FetchContent_MakeAvailable(Catch2)

# Main Executable
add_executable(MovieRecommender
        main.cpp
        AdjacencyList.cpp
        AdjacencyList.h
        AdjacencyMatrix.cpp
        AdjacencyMatrix.h
        GraphConstruct.cpp
        GraphConstruct.h
        Movie.h
)

# Test Executable
add_executable(tests
        test.cpp
        AdjacencyList.h
        AdjacencyList.cpp
        AdjacencyMatrix.h
        AdjacencyMatrix.cpp
        GraphConstruct.h
        GraphConstruct.cpp
        Movie.h
)

# Link test target to Catch2 with main
target_link_libraries(tests
        PRIVATE Catch2::Catch2WithMain
)

include(CTest)
enable_testing()
include(Catch)
catch_discover_tests(tests)