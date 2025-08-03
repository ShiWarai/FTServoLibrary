/**
 * @file SCS.hpp
 * @brief Коммуникационный слой протокола для серво-приводов Feetech
 * @date 19.06.2025
 * @author ShiWarai
 */

#ifndef _SCS_H
#define _SCS_H

#include "INST.hpp"

class SCS{
public:
	SCS();
	SCS(u8 End);
	SCS(u8 End, u8 Level);
	int genWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen);// Обычная команда записи
	int regWrite(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen);// Асинхронная команда записи
	int RegWriteAction(u8 ID = 0xfe);// Асинхронная команда выполнения записи
	void syncWrite(u8 ID[], u8 IDN, u8 MemAddr, u8 *nDat, u8 nLen);// Синхронная команда записи
	int writeByte(u8 ID, u8 MemAddr, u8 bDat);// Записать 1 байт
	int writeWord(u8 ID, u8 MemAddr, u16 wDat);// Записать 2 байта
	int Read(u8 ID, u8 MemAddr, u8 *nData, u8 nLen);// Команда чтения
	int readByte(u8 ID, u8 MemAddr);// Прочитать 1 байт
	int readWord(u8 ID, u8 MemAddr);// Прочитать 2 байта
	int Ping(u8 ID);// Команда Ping
	int syncReadPacketTx(u8 ID[], u8 IDN, u8 MemAddr, u8 nLen);// Отправить пакет синхронного чтения
	int syncReadPacketRx(u8 ID, u8 *nDat);// Декодировать ответный пакет синхронного чтения, возвращает число байт памяти при успехе, 0 при ошибке
	int syncReadRxPacketToByte();// Декодировать 1 байт
	int syncReadRxPacketToWrod(u8 negBit=0);// Декодировать 2 байта, negBit — направление, 0 — без направления
	void syncReadBegin(u8 IDN, u8 rxLen);// Начать синхронное чтение
	void syncReadEnd();// Завершить синхронное чтение
public:
	u8	Level;// Уровень ответа сервопривода
	u8	End;// Порядок байтов (big-endian/little-endian)
	u8	Error;// Состояние сервопривода
	u8 syncReadRxPacketIndex;
	u8 syncReadRxPacketLen;
	u8 *syncReadRxPacket;
	u8 *syncReadRxBuff;
	u16 syncReadRxBuffLen;
	u16 syncReadRxBuffMax;
protected:
	virtual int writeSCS(unsigned char *nDat, int nLen) = 0;
	virtual int readSCS(unsigned char *nDat, int nLen) = 0;
	virtual int writeSCS(unsigned char bDat) = 0;
	virtual void rFlushSCS() = 0;
	virtual void wFlushSCS() = 0;
protected:
	void writeBuf(u8 ID, u8 MemAddr, u8 *nDat, u8 nLen, u8 Fun);
	void Host2SCS(u8 *DataL, u8* DataH, u16 Data);// Разделить 16-битное число на два 8-битных
	u16	SCS2Host(u8 DataL, u8 DataH);// Объединить два 8-битных числа в одно 16-битное
	int	Ack(u8 ID);// Получить подтверждение
};
#endif