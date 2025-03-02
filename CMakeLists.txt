cmake_minimum_required(VERSION 3.31)
project(SWRMemTools VERSION 1.0.0)

add_library(SWRMemTools STATIC
    src/Save.cpp
    src/Shop.cpp
)
target_include_directories(SWRMemTools PRIVATE include)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v3.8.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests 
    #tests/test_32bit.cpp    
    tests/test_Save.cpp
    tests/test_Shop.cpp
)
target_include_directories(tests PRIVATE include)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(tests PRIVATE SWRMemTools)

include(CTest)
include(Catch)
catch_discover_tests(tests)