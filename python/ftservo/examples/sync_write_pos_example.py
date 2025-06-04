import ftservo
import time
import sys

# --- Настройте эти значения ---
BAUDRATE = 115200      # Скорость передачи данных (должна совпадать с настройками сервоприводов)

# Определяем ID сервоприводов, как в C++ примере
SERVO_ID_1 = 5
SERVO_ID_2 = 6
SERVO_IDS = [SERVO_ID_1, SERVO_ID_2] # Список для sync_write_pos

# Параметры движения
# Целевые позиции для двух шагов цикла
POSITION_STEP_1 = 500
POSITION_STEP_2 = 600

# Параметры движения для sync_write_pos
# Время движения в миллисекундах.
MOVE_TIME = 0 # ms (можно настроить)
MOVE_SPEED = 0  # 0 = макс. скорость для заданного времени
ACCELERATION = 0 # 0 = без ускорения

# Пауза между командами движения в секундах (75*1000 us = 75 ms)
PAUSE_DURATION = 0.075
# ---------------------------


if __name__ == "__main__":
    # Проверка аргументов командной строки, как в C++ примере
    if len(sys.argv) < 2:
        print(f"Usage: python {sys.argv[0]} <serial_port>")
        sys.exit(1)

    serial_port = sys.argv[1]
    print(f"Using serial port: {serial_port}")

    servo_controller = None # Инициализируем переменную контроллера как None

    try:
        print(f"Creating SCSCL object...")
        servo_controller = ftservo.SCSCL()
        print(f"SCSCL object created.")

        print(f"Initializing serial port {serial_port} with baudrate {BAUDRATE}...")
        if servo_controller.begin(BAUDRATE, serial_port):
            print(f"Serial port initialized successfully.")

            # --- Пинг двух двигателей (ID 5 и 6) ---
            print("\nPinging servos...")
            ping_id_1 = servo_controller.Ping(SERVO_ID_1)
            ping_id_2 = servo_controller.Ping(SERVO_ID_2)

            if ping_id_1 != -1:
                print(f"Ping successful for servo ID: {ping_id_1}")
            else:
                print(f"Ping failed for servo ID: {SERVO_ID_1}")

            if ping_id_2 != -1:
                print(f"Ping successful for servo ID: {ping_id_2}")
            else:
                print(f"Ping failed for servo ID: {SERVO_ID_2}")

            # --- Проверка результата пинга ---
            if ping_id_1 == -1 or ping_id_2 == -1:
                print("\nExiting due to failed ping.")
                # Соединение будет закрыто в блоке finally
                sys.exit(1) # Выходим, если пинг не удался для хотя бы одного серво

            print(f"\nStarting cyclic movement and reading for servos {SERVO_IDS}. Press Ctrl+C to stop.")

            # --- Параметры для sync_write_pos (нужны списки одинаковой длины) ---
            # Время, Скорость и Ускорение одинаковы для обоих сервоприводов в этом примере
            times_list = [MOVE_TIME] * len(SERVO_IDS)
            speeds_list = [MOVE_SPEED] * len(SERVO_IDS)
            accs_list = [ACCELERATION] * len(SERVO_IDS)

            # --- Бесконечный цикл движения и чтения ---
            while True:
                # --- Шаг 1: Двигаемся к позиции POSITION_STEP_1 ---
                positions_list_step1 = [POSITION_STEP_1] * len(SERVO_IDS)
                print(f"Moving servos {SERVO_IDS} to position {POSITION_STEP_1}")
                try:
                    servo_controller.sync_write_pos(
                        SERVO_IDS,
                        positions_list_step1,
                        times_list,
                        speeds_list,
                        accs_list
                    )
                    print(f"Command sent for position {POSITION_STEP_1}")
                except (ValueError, TypeError) as e:
                    print(f"Error sending sync_write_pos command: {e}")
                    break # Выходим из цикла при ошибке команды

                # Пауза, как в C++ примере
                time.sleep(PAUSE_DURATION)

                # --- Чтение и вывод текущего положения ---
                current_pos_1 = servo_controller.ReadPos(SERVO_ID_1)
                current_pos_2 = servo_controller.ReadPos(SERVO_ID_2)
                print(f"Servo {SERVO_ID_1} position: {current_pos_1}, Servo {SERVO_ID_2} position: {current_pos_2}")


                # --- Шаг 2: Двигаемся к позиции POSITION_STEP_2 ---
                positions_list_step2 = [POSITION_STEP_2] * len(SERVO_IDS)
                print(f"Moving servos {SERVO_IDS} to position {POSITION_STEP_2}")
                try:
                    servo_controller.sync_write_pos(
                        SERVO_IDS,
                        positions_list_step2,
                        times_list,
                        speeds_list,
                        accs_list
                    )
                    print(f"Command sent for position {POSITION_STEP_2}")
                except (ValueError, TypeError) as e:
                    print(f"Error sending sync_write_pos command: {e}")
                    break # Выходим из цикла при ошибке команды

                # Пауза, как в C++ примере
                time.sleep(PAUSE_DURATION)

                # --- Чтение и вывод текущего положения ---
                current_pos_1 = servo_controller.ReadPos(SERVO_ID_1)
                current_pos_2 = servo_controller.ReadPos(SERVO_ID_2)
                print(f"Servo {SERVO_ID_1} position: {current_pos_1}, Servo {SERVO_ID_2} position: {current_pos_2}")

            # Цикл завершится по KeyboardInterrupt или при ошибке команды
            print("\nExiting cyclic movement loop.")

        else: # Этот else относится к servo_controller.begin
            print(f"Failed to initialize serial port {serial_port}. Check port name, permissions, and baudrate.")
            sys.exit(1) # Выходим при ошибке инициализации порта

    except KeyboardInterrupt:
        # Обработка Ctrl+C для чистого выхода
        print("\nCyclic movement stopped by user (Ctrl+C).")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        # Дополнительная информация об ошибке, если доступна из контроллера
        if servo_controller:
             error_code = servo_controller.getErr()
             if error_code != 0:
                 print(f"Servo controller error code: {error_code}")

    finally:
        # Закрываем соединение с сервоприводом
        if servo_controller: # Проверяем, был ли объект успешно создан
            print(f"Closing serial connection...")
            servo_controller.end()
            print(f"Connection closed.")
        sys.exit(0) # Выходим из скрипта с кодом 0 (успех) или 1 (ошибка) 