cmake_minimum_required(VERSION 3.7)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(MathLibrary VERSION 1.0 DESCRIPTION "My C++ Math library" LANGUAGES CXX)

#adding the library
add_subdirectory( MathLibrary )
#Enable testing
enable_testing()

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
set(gtest_force_shared_crt ON)

FetchContent_MakeAvailable(googletest)

set( INC_FILES
    pch.h
)

set( SRC_FILES 
    pch.cpp
	test.cpp
)

add_executable( math_tests ${INC_FILES} ${SRC_FILES} )
target_link_libraries( math_tests PUBLIC gtest gtest_main )
gtest_discover_tests( math_tests )
target_link_libraries( math_tests PUBLIC MathLibrary )


set_target_properties(
    gmock
    gmock_main
    gtest
    gtest_main
    PROPERTIES FOLDER gtest
)
