cmake_minimum_required(VERSION 3.1.0)
project(libs)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(libs EditorParser.cpp ObjectCreator.cpp DomainObjects.cpp Commands.cpp Editor.cpp)