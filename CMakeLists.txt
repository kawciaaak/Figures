cmake_minimum_required(VERSION 3.0)
project(Figures)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define main file inside src folder
file(GLOB SRC_SOURCES "src/main.cpp")

# Zdefiniuj listę plików źródłowych w folderze figures
file(GLOB FIGURE_SOURCES "figures/*.cpp")
file(GLOB FIGURE_HEADERS "figures/*.h")


# Zdefiniuj listę plików źródłowych w folderze lib/collection
file(GLOB LIB_COLLECTION_SOURCES "lib/collection/collection.cpp")

# Zdefiniuj listę plików nagłówkowych w folderze lib/collection
file(GLOB LIB_COLLECTION_HEADERS "lib/collection/collection.h")

# Dodaj plik wykonywalny i podaj listę źródeł i nagłówków
add_executable(Figures ${SRC_SOURCES} ${INCLUDE_HEADERS} ${FIGURE_SOURCES} ${FIGURE_HEADERS} ${LIB_COLLECTION_SOURCES} ${LIB_COLLECTION_HEADERS})

# Dodaj katalog zawierający pliki nagłówkowe include
target_include_directories(Figures PUBLIC include)
