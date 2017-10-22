cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME TriNerdiICPC)
project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -Wno-sign-compare")

# This adds another subdirectory, which has 'project(gtest)'.
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable test_fft to see those specific tests.
enable_testing()

# Tests
set(SOURCES_LIST
    fft/fft
    fft/ntt
    treap/treap
    numth/prime
    numth/misc
    numth/modeq
    flow/dinic
    tree/lca
    tree/centroid
    tree/heavylight
    tree/heavylight2
)

foreach(CUR ${SOURCES_LIST})
    string(REPLACE "/" "_" UNDERSCORED "${CUR}")
    string(REGEX MATCH "^[^/]*" FST "${CUR}")
    string(REGEX MATCH "[^/]*$" SND "${CUR}")
    add_library(lib_${UNDERSCORED} src/${CUR}.cpp)
    add_executable(test_${UNDERSCORED} src/${CUR}_test.cpp)
    target_link_libraries(test_${UNDERSCORED} gtest gtest_main lib_${UNDERSCORED})
    add_test(test_${UNDERSCORED} test_${UNDERSCORED})
endforeach(CUR)
