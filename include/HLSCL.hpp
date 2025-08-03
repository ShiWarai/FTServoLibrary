/**
 * @file HLSCL.hpp
 * @brief Прикладной слой для серво-приводов серии Feetech HLSCL
 * @date 19.06.2025
 * @author ShiWarai
 */

#ifndef _HLSCL_H
#define _HLSCL_H

//-------EPROM (только чтение)--------
#define HLSCL_MODEL_L 3
#define HLSCL_MODEL_H 4

//-------EPROM (чтение/запись)--------
#define HLSCL_ID 5
#define HLSCL_BAUD_RATE 6
#define HLSCL_SECOND_ID 7
#define HLSCL_MIN_ANGLE_LIMIT_L 9
#define HLSCL_MIN_ANGLE_LIMIT_H 10
#define HLSCL_MAX_ANGLE_LIMIT_L 11
#define HLSCL_MAX_ANGLE_LIMIT_H 12
#define HLSCL_CW_DEAD 26
#define HLSCL_CCW_DEAD 27
#define HLSCL_OFS_L 31
#define HLSCL_OFS_H 32
#define HLSCL_MODE 33

//-------SRAM (чтение/запись)--------
#define HLSCL_TORQUE_ENABLE 40
#define HLSCL_ACC 41
#define HLSCL_GOAL_POSITION_L 42
#define HLSCL_GOAL_POSITION_H 43
#define HLSCL_GOAL_TORQUE_L 44
#define HLSCL_GOAL_TORQUE_H 45
#define HLSCL_GOAL_SPEED_L 46
#define HLSCL_GOAL_SPEED_H 47
#define HLSCL_TORQUE_LIMIT_L 48
#define HLSCL_TORQUE_LIMIT_H 49
#define HLSCL_LOCK 55

//-------SRAM (только чтение)--------
#define HLSCL_PRESENT_POSITION_L 56
#define HLSCL_PRESENT_POSITION_H 57
#define HLSCL_PRESENT_SPEED_L 58
#define HLSCL_PRESENT_SPEED_H 59
#define HLSCL_PRESENT_LOAD_L 60
#define HLSCL_PRESENT_LOAD_H 61
#define HLSCL_PRESENT_VOLTAGE 62
#define HLSCL_PRESENT_TEMPERATURE 63
#define HLSCL_MOVING 66
#define HLSCL_PRESENT_CURRENT_L 69
#define HLSCL_PRESENT_CURRENT_H 70

#include "SCSerial.hpp"

class HLSCL : public SCSerial
{
public:
	HLSCL();
	HLSCL(u8 End);
	HLSCL(u8 End, u8 Level);
	int WritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0, u16 Torque = 0);// Обычная запись позиции для одного сервопривода
	int RegWritePosEx(u8 ID, s16 Position, u16 Speed, u8 ACC = 0, u16 Torque = 0);// Асинхронная запись позиции для одного сервопривода (активируется RegWriteAction)
	void SyncWritePosEx(u8 ID[], u8 IDN, s16 Position[], u16 Speed[], u8 ACC[], u16 Torque[]);// Синхронная запись позиции для нескольких сервоприводов
	void SyncWriteSpe(u8 ID[], u8 IDN, s16 Speed[], u8 ACC[], u16 Torque[]);// Синхронная запись скорости для нескольких сервоприводов
	int ServoMode(u8 ID);// Режим сервопривода
	int WheelMode(u8 ID);// Режим колеса
	int EleMode(u8 ID);// Режим постоянного усилия
	int WriteSpe(u8 ID, s16 Speed, u8 ACC = 0, u16 Torque = 0);// Управление скоростью в режиме колеса
	int WriteEle(u8 ID, s16 Torque);// Управление усилием в режиме постоянного усилия
	int EnableTorque(u8 ID, u8 Enable);// Управление моментом
	int unLockEprom(u8 ID);// Разблокировать EPROM
	int LockEprom(u8 ID);// Заблокировать EPROM
	int CalibrationOfs(u8 ID);// Калибровка среднего положения
	int FeedBack(int ID);// Получить обратную связь
	int ReadPos(int ID);// Прочитать позицию
	int ReadSpeed(int ID);// Прочитать скорость
	int ReadLoad(int ID);// Прочитать нагрузку (процент напряжения на моторе 0~1000)
	int ReadVoltage(int ID);// Прочитать напряжение
	int ReadTemper(int ID);// Прочитать температуру
	int ReadMove(int ID);// Прочитать состояние движения
	int ReadCurrent(int ID);// Прочитать ток
private:
	u8 Mem[HLSCL_PRESENT_CURRENT_H-HLSCL_PRESENT_POSITION_L+1];
};

#endif 