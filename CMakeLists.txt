cmake_minimum_required(VERSION 2.8.12)
project(MaximumEmptyRectangle)

add_definitions("-std=c++14")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(mer_test mer_test.cpp)
target_link_libraries(mer_test ${CONAN_LIBS})
