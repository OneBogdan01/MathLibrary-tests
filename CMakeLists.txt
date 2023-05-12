cmake_minimum_required(VERSION 3.7)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(MathLibrary VERSION 1.0 DESCRIPTION "My C++ Math library" LANGUAGES CXX)

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
	MathLibrary/CorePhysics.hpp
    MathLibrary/Transform.hpp
    MathLibrary/MathFunctions.hpp
    MathLibrary/World.hpp
)

set( SRC_FILES 
    pch.cpp
	test.cpp
    MathLibrary/Transform.cpp
    MathLibrary/MathFunctions.cpp
    MathLibrary/World.cpp
)

add_executable( math_tests ${INC_FILES} ${SRC_FILES} )
target_link_libraries( math_tests PUBLIC gtest gtest_main )
gtest_discover_tests( math_tests )

set_target_properties(
    gmock
    gmock_main
    gtest
    gtest_main
    PROPERTIES FOLDER gtest
)
