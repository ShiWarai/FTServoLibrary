/*
 * SCSerial.hpp
 * Аппаратный интерфейсный слой для серво-приводов Feetech
 * Дата: 2022.3.29
 * Автор: 
 */

#ifndef _SCSERIAL_H
#define _SCSERIAL_H

#include "SCS.hpp"
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>

#define DEFAULT_IOTIMEOUT 500

class SCSerial : public SCS
{
public:
	enum InterfaceType {
		INTERFACE_UNKNOWN, // Неизвестный тип (для будущих расширений)
        INTERFACE_USB,  // USB-порт (например, /dev/ttyUSB0)
        INTERFACE_UART // UART-порт (например, /dev/ttyS0)
    };

    SCSerial();
    SCSerial(u8 End);
    SCSerial(u8 End, u8 Level);

protected:
    int writeSCS(unsigned char *nDat, int nLen); // Вывод nLen байт
    int readSCS(unsigned char *nDat, int nLen);  // Ввод nLen байт
    int writeSCS(unsigned char bDat);            // Вывод 1 байта
    void rFlushSCS();                            // Очистка буфера чтения
    void wFlushSCS();                            // Очистка буфера записи
public:
    unsigned long int IOTimeOut = DEFAULT_IOTIMEOUT; // Таймаут ввода-вывода
    int Err;

    virtual int getErr() { return Err; }
    virtual int setBaudRate(int baudRate);
    virtual bool begin(int baudRate, const char* serialPort);
    virtual void end();
protected:
    int fd;                     // Дескриптор порта
    struct termios orgopt;      // Исходные настройки порта
    struct termios curopt;      // Текущие настройки порта
    unsigned char txBuf[255];   // Буфер передачи
    int txBufLen;               // Длина буфера передачи
    InterfaceType interfaceType;// Тип интерфейса
};

#endif