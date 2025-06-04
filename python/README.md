# FTServo Python Package

This package provides Python bindings for the FTServoLibrary, allowing control of Feetech servos from Python.
It is built upon the C++ library for performance.

## Сборка и Установка

Сборка Python пакета осуществляется с помощью скрипта `./build.sh` в корневой директории проекта. Убедитесь, что у вас установлены все зависимости для сборки C++ и Python (см. главный `README.md`).

Для сборки C++ библиотеки и Python пакета выполните в корне проекта:

```bash
./build.sh --python
```

После успешной сборки, `.whl` файл пакета будет находиться в директории `python/dist/`. Вы можете установить его с помощью pip:

```bash
pip install ./python/dist/*.whl
```

## Использование

Импортируйте пакет `ftservo`:

```python
import ftservo

# Пример создания объекта SCSCL и инициализации порта
try:
    controller = ftservo.SCSCL()
    if controller.begin(115200, "/dev/ttyUSB0"): # Укажите ваш порт и скорость
        print("Successfully initialized")
        # Далее можно использовать методы контроллера, например:
        # servo_id = 1
        # position = controller.ReadPos(servo_id)
        # print(f"Servo {servo_id} position: {position}")
    else:
        print("Failed to initialize serial port")
except Exception as e:
    print(f"An error occurred: {e}")
finally:
    if 'controller' in locals() and controller:
        controller.end()
        print("Serial connection closed")
```

Для подробных примеров смотрите файлы в директории `ftservo/examples/` после установки пакета или в исходниках (`python/ftservo/examples/`).

Запуск примера `sync_write_pos_example.py` (после установки пакета):

```bash
python -m ftservo.examples.sync_write_pos_example /dev/ttyUSB0 # Укажите ваш порт
```

## Требования

- Python 3.10+
- Собраная C++ библиотека FTServoLibrary (обеспечивается скриптом `build.sh`)

## Лицензия

Данный пакет распространяется под лицензией MIT. Подробнее см. файл `LICENSE` в корневой директории проекта.
