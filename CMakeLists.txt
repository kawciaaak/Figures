cmake_minimum_required(VERSION 3.0)
project(Figures)

# Ustawienie opcji kompilacji
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodanie plików źródłowych do kompilacji
file(GLOB SOURCES "src/*.cpp")

# Dodanie plików nagłówkowych
file(GLOB HEADERS "include/*.h")

# Dodanie katalogu z plikami nagłówkowymi
include_directories(include)

# Dodanie pliku wykonywalnego
add_executable(Figures ${SOURCES} ${HEADERS})