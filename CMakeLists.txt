cmake_minimum_required(VERSION 3.0)
project(Figures)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

file(GLOB HEADERS "include/*.h")

include_directories(include)

add_executable(Figures ${SOURCES} ${HEADERS})