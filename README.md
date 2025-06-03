# FTServoLibrary
Библиотека для управления двигателями Feetech с Linux. Сделано специально для проекта RDS-2P.

# Сборка библиотеки как libSCServo.a
- sudo apt update && sudo apt install libstdc++-dev
- mkdir build && cd build
- cmake .. && cmake --build .

# Тестирование
- cd examples/SCSCL/Ping
- mkdir build && cd build
- rm -rf CMakeFiles &&  cmake .. && cmake --build .
- sudo ./Ping /dev/ttyS7 1
