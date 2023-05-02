cmake_minimum_required(VERSION 3.7)


project(MathLibrary VERSION 1.0 DESCRIPTION "My C++ Math library" LANGUAGES CXX)


#add_library(one STATIC two.cpp three.h) for adding libraries (SHARED STATIC MOULE)

add_library(g_test STATIC src/CorePhysics.hpp pch.cpp)
target_include_directories(g_test PUBLIC packages ./src packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.7/build/native/include)
target_compile_features(g_test PUBLIC cxx_std_11)

add_executable(math_tests test.cpp)
target_link_libraries(math_tests PUBLIC g_test)
