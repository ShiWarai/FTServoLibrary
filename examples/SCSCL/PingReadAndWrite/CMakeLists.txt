cmake_minimum_required(VERSION 3.20)
set(project "PingReadAndWrite")
project(${project})

# Устанавливаем стандарт C++17 (синхронизируем с основным проектом)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем флаги компиляции (оптимизация O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Собираем исходные файлы
file(GLOB srs "*.cpp")
file(GLOB hdrs "*.hpp")

# Создаем исполняемый файл
add_executable(${project} ${srs} ${hdrs})

# Линкуем библиотеку SCServo
target_link_libraries(${project} PRIVATE FTServo_shared)

# Указываем пути к заголовочным файлам из основного проекта
target_include_directories(${project} PRIVATE ${CMAKE_SOURCE_DIR}/../../../include)
