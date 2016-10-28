cmake_minimum_required(VERSION 2.8)

# Make PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR, and PROJECT_NAME available.
set(PROJECT_NAME TriNerdiICPC)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall -Wno-sign-compare")

# If you want your own include/ directory, set this, and then you can do
# include_directories(${COMMON_INCLUDES}) in other CMakeLists.txt files.
# set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

################################
# Normal Libraries & Executables
################################
add_library(lib_fft src/fft/fft.cpp)

################################
# Testing
################################
# This adds another subdirectory, which has 'project(gtest)'.
add_subdirectory(lib/googletest)

enable_testing()

# Include the gtest library. gtest_SOURCE_DIR is available due to
# 'project(gtest)' above.
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

##############
# Unit Tests
##############
add_executable(test_fft src/fft/fft_test.cpp)
# Standard linking to gtest stuff; Extra linking for the project.
target_link_libraries(test_fft gtest gtest_main lib_fft)

# This is so you can do 'make test' to see all your tests run, instead of
# manually running the executable test_fft to see those specific tests.
add_test(NAME fft-test COMMAND test_fft)
# You can also omit NAME and COMMAND. The second argument could be some other
# test executable.
add_test(other-fft-test test_fft)