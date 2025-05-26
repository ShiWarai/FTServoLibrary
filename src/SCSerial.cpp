/*
 * SCSerial.cpp
 * 飞特串行舵机硬件接口层程序
 * 日期: 2022.3.29
 * 作者: 
 */

#include "SCSerial.hpp"

SCSerial::SCSerial()
{
    IOTimeOut = 100;
    fd = -1;
    txBufLen = 0;
    interfaceType = INTERFACE_UNKNOWN;
}

SCSerial::SCSerial(u8 End) : SCS(End)
{
    IOTimeOut = 100;
    fd = -1;
    txBufLen = 0;
    interfaceType = INTERFACE_UNKNOWN;
}

SCSerial::SCSerial(u8 End, u8 Level) : SCS(End, Level)
{
    IOTimeOut = 100;
    fd = -1;
    txBufLen = 0;
    interfaceType = INTERFACE_UNKNOWN;
}

bool SCSerial::begin(int baudRate, const char* serialPort)
{
    if (fd != -1) {
        close(fd);
        fd = -1;
    }

    if (serialPort == NULL) {
        return false;
    }

    // Определяем тип порта (USB или UART) по имени
    if (strstr(serialPort, "ttyUSB") != NULL) {
        interfaceType = INTERFACE_USB;
    } else if (strstr(serialPort, "ttyS") != NULL || strstr(serialPort, "ttyAMA") != NULL) {
        interfaceType = INTERFACE_UART;
    } else {
        printf("Unknown port type: %s, assuming UART\n", serialPort);
        interfaceType = INTERFACE_UNKNOWN;
    }

    // Открываем порт
    // Для USB используем неблокирующий режим, для UART — блокирующий
    int flags = O_RDWR | O_NOCTTY;
    if (interfaceType == INTERFACE_USB) {
        flags |= O_NONBLOCK; // Неблокирующий режим для USB
    }
    fd = open(serialPort, flags);
    if (fd == -1) {
        perror("open:");
        return false;
    }

    // Сохраняем текущие настройки порта
    if (tcgetattr(fd, &orgopt) != 0) {
        perror("tcgetattr:");
        close(fd);
        fd = -1;
        return false;
    }

    // Копируем настройки в curopt для модификации
    curopt = orgopt;

    // Устанавливаем скорость передачи данных
    speed_t CR_BAUDRATE;
    switch (baudRate) {
    case 9600:
        CR_BAUDRATE = B9600;
        break;
    case 19200:
        CR_BAUDRATE = B19200;
        break;
    case 38400:
        CR_BAUDRATE = B38400;
        break;
    case 57600:
        CR_BAUDRATE = B57600;
        break;
    case 115200:
        CR_BAUDRATE = B115200;
        break;
    case 500000:
        CR_BAUDRATE = B500000;
        break;
    case 1000000:
        CR_BAUDRATE = B1000000;
        break;
    default:
        CR_BAUDRATE = B115200;
        break;
    }
    cfsetispeed(&curopt, CR_BAUDRATE);
    cfsetospeed(&curopt, CR_BAUDRATE);

    printf("serial speed %d on %s (type: %s)\n", baudRate, serialPort,
            interfaceType == INTERFACE_USB ? "USB" : "UART");

    // Настройка параметров порта (8N1, без управления потоком)
    curopt.c_cflag &= ~PARENB;    // Без четности
    curopt.c_cflag &= ~CSTOPB;    // 1 стоп-бит
    curopt.c_cflag &= ~CSIZE;     // Очистка размера данных
    curopt.c_cflag |= CS8;        // 8 бит данных
    curopt.c_cflag |= CREAD;      // Включить чтение
    curopt.c_cflag |= CLOCAL;     // Отключить проверку модема
    curopt.c_iflag &= ~(IXON | IXOFF | IXANY); // Отключить управление потоком
    curopt.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Режим raw
    curopt.c_oflag &= ~OPOST;     // Отключить обработку вывода
    curopt.c_lflag = 0;           // Отключить локальные режимы

    // Устанавливаем таймаут чтения
    curopt.c_cc[VMIN] = 0;        // Минимальное количество символов
    curopt.c_cc[VTIME] = 1;       // Таймаут 0.1 сек (для USB и UART)

    // Применяем настройки
    if (tcsetattr(fd, TCSANOW, &curopt) != 0) {
        perror("tcsetattr:");
        close(fd);
        fd = -1;
        return false;
    }

    // Очищаем буферы ввода-вывода
    tcflush(fd, TCIOFLUSH);

    return true;
}

int SCSerial::setBaudRate(int baudRate)
{
    if (fd == -1) {
        return -1;
    }

    tcgetattr(fd, &orgopt);
    tcgetattr(fd, &curopt);

    speed_t CR_BAUDRATE;
    switch (baudRate) {
    case 9600:
        CR_BAUDRATE = B9600;
        break;
    case 19200:
        CR_BAUDRATE = B19200;
        break;
    case 38400:
        CR_BAUDRATE = B38400;
        break;
    case 57600:
        CR_BAUDRATE = B57600;
        break;
    case 115200:
        CR_BAUDRATE = B115200;
        break;
    case 230400:
        CR_BAUDRATE = B230400;
        break;
    case 500000:
        CR_BAUDRATE = B500000;
        break;
    default:
        return -1;
    }

    cfsetispeed(&curopt, CR_BAUDRATE);
    cfsetospeed(&curopt, CR_BAUDRATE);

    if (tcsetattr(fd, TCSANOW, &curopt) != 0) {
        perror("tcsetattr:");
        return -1;
    }

    return 1;
}

int SCSerial::readSCS(unsigned char *nDat, int nLen)
{
    int rvLen = 0;
    struct timeval time;
    fd_set fs_read;

    FD_ZERO(&fs_read);
    FD_SET(fd, &fs_read);

    time.tv_sec = 0;
    time.tv_usec = IOTimeOut * 1000;

    while (rvLen < nLen) {
        int fs_sel = select(fd + 1, &fs_read, NULL, NULL, &time);
        if (fs_sel > 0) {
            int bytesRead = read(fd, nDat + rvLen, nLen - rvLen);
            if (bytesRead <= 0) {
                break; // Ошибка чтения или конец данных
            }
            rvLen += bytesRead;
        } else {
            break; // Таймаут или ошибка
        }
    }

    return rvLen;
}

int SCSerial::writeSCS(unsigned char *nDat, int nLen)
{
    while (nLen--) {
        txBuf[txBufLen++] = *nDat++;
    }
    return txBufLen;
}

int SCSerial::writeSCS(unsigned char bDat)
{
    txBuf[txBufLen++] = bDat;
    return txBufLen;
}

void SCSerial::rFlushSCS()
{
    tcflush(fd, TCIFLUSH);
}

void SCSerial::wFlushSCS()
{
    if (txBufLen) {
        int bytesWritten = write(fd, txBuf, txBufLen);
        if (bytesWritten < 0) {
            perror("write:");
        }
        txBufLen = 0;
    }
}

void SCSerial::end()
{
    if (fd != -1) {
        tcsetattr(fd, TCSANOW, &orgopt); // Восстанавливаем исходные настройки
        close(fd);
        fd = -1;
    }
}