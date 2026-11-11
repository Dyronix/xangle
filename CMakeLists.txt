cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(xangle LANGUAGES CXX)

add_library(xangle INTERFACE)
add_library(xangle::xangle ALIAS xangle)

target_sources(xangle INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include/angle.h)
target_include_directories(xangle INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_features(xangle INTERFACE cxx_std_20)

set_target_properties(xangle PROPERTIES FOLDER "ThirdParty/XAngle")

option(XANGLE_BUILD_TESTS "Build the xangle compile-time tests" ${PROJECT_IS_TOP_LEVEL})
if(XANGLE_BUILD_TESTS)
  add_executable(xangle_tests tests/angle_tests.cpp)
  target_link_libraries(xangle_tests PRIVATE xangle::xangle)
endif()
