cmake_minimum_required(VERSION 3.0)
project(Figures)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define main file inside src folder
file(GLOB SOURCES "src/main.cpp")

# Define source files list in the figures folder
file(GLOB FIGURE_SOURCES "figures/*.cpp")
file(GLOB FIGURE_HEADERS "figures/*.h")

# Define source files list in the lib/collection folder
file(GLOB LIB_COLLECTION_SOURCES "lib/collection/collection.cpp")

# Define header files list in the lib/collection folder
file(GLOB LIB_COLLECTION_HEADERS "lib/collection/collection.h")

# Add executable and specify source and header files
add_executable(Figures ${SRC_SOURCES} ${INCLUDE_HEADERS} ${FIGURE_SOURCES} ${FIGURE_HEADERS} ${LIB_COLLECTION_SOURCES} ${LIB_COLLECTION_HEADERS})

# Add directory containing include header files
target_include_directories(Figures PUBLIC include)
