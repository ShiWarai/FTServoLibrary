#!/bin/bash
# Скрипт для сборки C++ библиотеки и Python пакета

# Выход при любой ошибке
set -e

# Переменная для имени виртуального окружения
VENV_NAME=".dev-venv"

# Флаги сборки
BUILD_CPP=false
BUILD_PYTHON=false

# Парсинг аргументов командной строки
if [ $# -eq 0 ]; then
    # Default behavior: build only CPP
    BUILD_CPP=true
else
    for arg in "$@"
    do
        case $arg in
            --python)
            BUILD_CPP=true # Python сборка зависит от C++
            BUILD_PYTHON=true
            ;;
            *)
            echo "Неизвестный аргумент: $arg"
            echo "Использование: ./build.sh [--python]"
            exit 1
            ;;
        esac
    done
fi

if [ "$BUILD_CPP" = true ]; then
    echo "--- Шаг 1: Сборка C++ библиотеки ---"
    # Создаем директорию build, если ее нет, и переходим в нее
    mkdir -p build
    cd build

    # Запускаем CMake и Make
    # Убедитесь, что в корневом CMakeLists.txt есть команды для сборки библиотеки
    cmake ..
    make

    # Возвращаемся в корень проекта
    cd ..
fi

if [ "$BUILD_PYTHON" = true ]; then
    echo "--- Шаг 2: Подготовка Python окружения и сборка пакета (включая заглушки) ---"
    # Переходим в директорию Python
    cd python

    # Проверяем наличие виртуального окружения, создаем и активируем его
    if [ ! -d "$VENV_NAME" ]; then
        echo "Виртуальное окружение '$VENV_NAME' не найдено. Создаем..."
        python3 -m venv "$VENV_NAME"
        echo "Виртуальное окружение '$VENV_NAME' создано."
    fi

    echo "Активируем виртуальное окружение '$VENV_NAME'..."
    source "$VENV_NAME"/bin/activate

    echo "Устанавливаем зависимости Python для сборки и генерации заглушек..."
    pip install -r requirements.txt
    pip install pybind11-stubgen build # Убедимся, что эти инструменты установлены

    echo "Собираем Python пакет (.whl и .tar.gz) в первый раз (пока без заглушек)..."
    # Удаляем предыдущие сборки перед первой сборкой, чтобы избежать путаницы
    rm -rf dist/*
    python -m build

    echo "--- Шаг 3: Установка пакета (.whl) и генерация заглушек ---"
    # Устанавливаем только что собранный .whl пакет. Это нужно для pybind11-stubgen.
    # Используем --force-reinstall чтобы обновить, если уже установлен
    # --no-deps чтобы не устанавливать зависимости снова
    pip install dist/*.whl --force-reinstall --no-deps

    echo "Генерируем заглушки (.pyi)..."
    # Генерируем заглушки в директорию с исходниками пакета ftservo.
    # Предполагаем, что ваша структура такая: python/ftservo/__init__.py или python/ftservo/ftservo.so
    # Укажите правильную директорию для -o если структура другая.
    STUB_OUTPUT_DIR="ftservo" # Директория, куда pybind11-stubgen поместит ftservo.pyi
    mkdir -p "$STUB_OUTPUT_DIR" # Создаем директорию, если ее нет (на всякий случай)
    pybind11-stubgen ftservo -o .

    echo "--- Шаг 4: Пересборка пакета (включая сгенерированные заглушки) ---"
    # Теперь, когда ftservo.pyi находится в директории ftservo/,
    # python -m build должен включить его.
    echo "Пересобираем Python пакет, теперь с включенными заглушками..."
    # Удаляем предыдущие сборки перед второй сборкой
    rm -rf dist/*
    # Собираем снова
    python -m build

    echo "--- Шаг 5: Очистка и Завершение ---"
    echo "Сборка и генерация заглушек завершены успешно. Окончательный .whl находится в python/dist/."

    # Возвращаемся в корень проекта
    cd ..
fi