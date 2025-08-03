/**
 * @file SMSBL.hpp
 * @brief Прикладной слой для серво-приводов серии Feetech SMSBL
 * @date 19.06.2025
 * @author ShiWarai
 */

#ifndef _SMSBL_H
#define _SMSBL_H

// Определения скоростей передачи
#define	SMSBL_1M 0
#define	SMSBL_0_5M 1
#define	SMSBL_250K 2
#define	SMSBL_128K 3
#define	SMSBL_115200 4
#define	SMSBL_76800	5
#define	SMSBL_57600	6
#define	SMSBL_38400	7

// Определения памяти
//-------EPROM (только чтение)--------
#define SMSBL_MODEL_L 3
#define SMSBL_MODEL_H 4

//-------EPROM (чтение/запись)--------
#define SMSBL_ID 5
#define SMSBL_BAUD_RATE 6
#define SMSBL_MIN_ANGLE_LIMIT_L 9
#define SMSBL_MIN_ANGLE_LIMIT_H 10
#define SMSBL_MAX_ANGLE_LIMIT_L 11
#define SMSBL_MAX_ANGLE_LIMIT_H 12
#define SMSBL_CW_DEAD 26
#define SMSBL_CCW_DEAD 27
#define SMSBL_OFS_L 31
#define SMSBL_OFS_H 32
#define SMSBL_MODE 33

//-------SRAM (чтение/запись)--------
#define SMSBL_TORQUE_ENABLE 40
#define SMSBL_ACC 41
#define SMSBL_GOAL_POSITION_L 42
#define SMSBL_GOAL_POSITION_H 43
#define SMSBL_GOAL_TIME_L 44
#define SMSBL_GOAL_TIME_H 45
#define SMSBL_GOAL_SPEED_L 46
#define SMSBL_GOAL_SPEED_H 47
#define SMSBL_LOCK 55

//-------SRAM (только чтение)--------
#define SMSBL_PRESENT_POSITION_L 56
#define SMSBL_PRESENT_POSITION_H 57
#define SMSBL_PRESENT_SPEED_L 58
#define SMSBL_PRESENT_SPEED_H 59
#define SMSBL_PRESENT_LOAD_L 60
#define SMSBL_PRESENT_LOAD_H 61
#define SMSBL_PRESENT_VOLTAGE 62
#define SMSBL_PRESENT_TEMPERATURE 63
#define SMSBL_MOVING 66
#define SMSBL_PRESENT_CURRENT_L 69
#define SMSBL_PRESENT_CURRENT_H 70

#include "SCSerial.hpp"

class SMSBL : public SCSerial
{
public:
	SMSBL();
	SMSBL(u8 End);
	SMSBL(u8 End, u8 Level);
	virtual int WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);// Обычная запись позиции для одного сервопривода
	virtual int RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0);// Асинхронная запись позиции для одного сервопривода (активируется RegWriteAction)
	virtual void SyncWritePosEx(u8 ID[], u8 IDN, s16 Position[], u16 Speed[], u8 ACC[]);// Синхронная запись позиции для нескольких сервоприводов
	virtual int WheelMode(u8 ID);// Режим колеса
	virtual int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0);// Управление скоростью в режиме колеса
	virtual int EnableTorque(u8 ID, u8 Enable);// Управление моментом
	virtual int unLockEprom(u8 ID);// Разблокировать EPROM
	virtual int LockEprom(u8 ID);// Заблокировать EPROM
	virtual int CalibrationOfs(u8 ID);// Калибровка среднего положения
	virtual int FeedBack(int ID);// Получить обратную связь
	virtual int ReadPos(int ID);// Прочитать позицию
	virtual int ReadSpeed(int ID);// Прочитать скорость
	virtual int ReadLoad(int ID);// Прочитать нагрузку (процент напряжения на моторе 0~1000)
	virtual int ReadVoltage(int ID);// Прочитать напряжение
	virtual int ReadTemper(int ID);// Прочитать температуру
	virtual int ReadMove(int ID);// Прочитать состояние движения
	virtual int ReadCurrent(int ID);// Прочитать ток
private:
	u8 Mem[SMSBL_PRESENT_CURRENT_H-SMSBL_PRESENT_POSITION_L+1];
};

#endif