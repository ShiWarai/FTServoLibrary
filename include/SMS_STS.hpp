/**
 * @file SMS_STS.hpp
 * @brief Прикладной слой для серво-приводов серии Feetech SMS/STS
 * @date 19.06.2025
 * @author ShiWarai
 */

#ifndef _SMS_STS_H
#define _SMS_STS_H

// Определения скоростей передачи
#define	SMS_STS_1M 0
#define	SMS_STS_0_5M 1
#define	SMS_STS_250K 2
#define	SMS_STS_128K 3
#define	SMS_STS_115200 4
#define	SMS_STS_76800 5
#define	SMS_STS_57600 6
#define	SMS_STS_38400 7

// Определения памяти
//-------EPROM (только чтение)--------
#define SMS_STS_MODEL_L 3
#define SMS_STS_MODEL_H 4

//-------EPROM (чтение/запись)--------
#define SMS_STS_ID 5
#define SMS_STS_BAUD_RATE 6
#define SMS_STS_MIN_ANGLE_LIMIT_L 9
#define SMS_STS_MIN_ANGLE_LIMIT_H 10
#define SMS_STS_MAX_ANGLE_LIMIT_L 11
#define SMS_STS_MAX_ANGLE_LIMIT_H 12
#define SMS_STS_CW_DEAD 26
#define SMS_STS_CCW_DEAD 27
#define SMS_STS_OFS_L 31
#define SMS_STS_OFS_H 32
#define SMS_STS_MODE 33

//-------SRAM (чтение/запись)--------
#define SMS_STS_TORQUE_ENABLE 40
#define SMS_STS_ACC 41
#define SMS_STS_GOAL_POSITION_L 42
#define SMS_STS_GOAL_POSITION_H 43
#define SMS_STS_GOAL_TIME_L 44
#define SMS_STS_GOAL_TIME_H 45
#define SMS_STS_GOAL_SPEED_L 46
#define SMS_STS_GOAL_SPEED_H 47
#define SMS_STS_LOCK 55

//-------SRAM (только чтение)--------
#define SMS_STS_PRESENT_POSITION_L 56
#define SMS_STS_PRESENT_POSITION_H 57
#define SMS_STS_PRESENT_SPEED_L 58
#define SMS_STS_PRESENT_SPEED_H 59
#define SMS_STS_PRESENT_LOAD_L 60
#define SMS_STS_PRESENT_LOAD_H 61
#define SMS_STS_PRESENT_VOLTAGE 62
#define SMS_STS_PRESENT_TEMPERATURE 63
#define SMS_STS_MOVING 66
#define SMS_STS_PRESENT_CURRENT_L 69
#define SMS_STS_PRESENT_CURRENT_H 70

#include "SCSerial.hpp"

class SMS_STS : public SCSerial
{
public:
	SMS_STS();
	SMS_STS(u8 End);
	SMS_STS(u8 End, u8 Level);
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
	u8 Mem[SMS_STS_PRESENT_CURRENT_H-SMS_STS_PRESENT_POSITION_L+1];
};

#endif