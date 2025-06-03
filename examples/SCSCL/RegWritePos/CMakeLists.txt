cmake_minimum_required(VERSION 3.20)
set(project "RegWritePos")
project(${project})

# Устанавливаем стандарт C++17 (синхронизируем с основным проектом)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компиляции (оптимизация O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Указываем путь к заголовочным файлам библиотеки
include_directories(${CMAKE_SOURCE_DIR}/../../../include)

# Указываем путь к библиотеке
link_directories(${CMAKE_SOURCE_DIR}/../../../build)

# Собираем исходные файлы примера
file(GLOB srs *.cpp)
file(GLOB hdrs *.hpp)

# Создаем исполняемый файл
add_executable(${project} ${srs} ${hdrs})

# Линкуем библиотеку SCServo
target_link_libraries(${project} PRIVATE FTServo)