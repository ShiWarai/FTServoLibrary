cmake_minimum_required(VERSION 3.20)
set(project "FTServo")
project(${project})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

# Указываем пути к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/include)

# Собираем все исходные файлы из src/
file(GLOB srs ${CMAKE_SOURCE_DIR}/src/*.cpp)
# Собираем все заголовочные файлы из include/SCServo/
file(GLOB hdrs ${CMAKE_SOURCE_DIR}/include/*.hpp)

# Создаем статическую библиотеку
add_library(${project} STATIC ${srs} ${hdrs})
