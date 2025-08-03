/**
 * @file SCSCL.hpp
 * @brief Прикладной слой для серво-приводов серии Feetech SCSCL
 * @date 19.06.2025
 * @author ShiWarai
 */

#ifndef _SCSCL_H
#define _SCSCL_H


#define	SCSCL_1M 0
#define	SCSCL_0_5M 1
#define	SCSCL_250K 2
#define	SCSCL_128K 3
#define	SCSCL_115200 4
#define	SCSCL_76800	5
#define	SCSCL_57600	6
#define	SCSCL_38400	7

//-------EPROM (только чтение)--------
#define SCSCL_VERSION_L 3
#define SCSCL_VERSION_H 4

//-------EPROM (чтение/запись)--------
#define SCSCL_ID 5
#define SCSCL_BAUD_RATE 6
#define SCSCL_MIN_ANGLE_LIMIT_L 9
#define SCSCL_MIN_ANGLE_LIMIT_H 10
#define SCSCL_MAX_ANGLE_LIMIT_L 11
#define SCSCL_MAX_ANGLE_LIMIT_H 12
#define SCSCL_CW_DEAD 26
#define SCSCL_CCW_DEAD 27

//-------SRAM (чтение/запись)--------
#define SCSCL_TORQUE_ENABLE 40
#define SCSCL_GOAL_ACCELERATION 41
#define SCSCL_GOAL_POSITION_L 42
#define SCSCL_GOAL_POSITION_H 43
#define SCSCL_GOAL_TIME_L 44
#define SCSCL_GOAL_TIME_H 45
#define SCSCL_GOAL_SPEED_L 46
#define SCSCL_GOAL_SPEED_H 47
#define SCSCL_LOCK 48

//-------SRAM (только чтение)--------
#define SCSCL_PRESENT_POSITION_L 56
#define SCSCL_PRESENT_POSITION_H 57
#define SCSCL_PRESENT_SPEED_L 58
#define SCSCL_PRESENT_SPEED_H 59
#define SCSCL_PRESENT_LOAD_L 60
#define SCSCL_PRESENT_LOAD_H 61
#define SCSCL_PRESENT_VOLTAGE 62
#define SCSCL_PRESENT_TEMPERATURE 63
#define SCSCL_MOVING 66
#define SCSCL_PRESENT_CURRENT_L 69
#define SCSCL_PRESENT_CURRENT_H 70

#include "SCSerial.hpp"

class SCSCL : public SCSerial
{
public:
	SCSCL();
	SCSCL(u8 End);
	SCSCL(u8 End, u8 Level);
	virtual int WritePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Acc);// Обычная команда записи позиции для одного сервопривода
	virtual int RegWritePos(u8 ID, u16 Position, u16 Time, u16 Speed, u8 Acc);// Регистровая (отложенная) команда записи позиции для одного сервопривода (активируется RegWriteAction)
	virtual void SyncWritePos(u8 ID[], u8 IDN, u16 Position[], u16 Time[], u16 Speed[], u8 Acc[]);// Синхронная команда записи позиции для нескольких сервоприводов
	virtual int PWMMode(u8 ID);// Включить режим PWM
	virtual int WritePWM(u8 ID, s16 pwmOut);// Команда управления PWM
	virtual int EnableTorque(u8 ID, u8 Enable);// Управление включением/отключением момента
	virtual int unLockEprom(u8 ID);// Разблокировать EPROM
	virtual int LockEprom(u8 ID);// Заблокировать EPROM
	virtual int FeedBack(int ID);// Получить обратную связь от сервопривода
	virtual int ReadPos(int ID);// Прочитать позицию
	virtual int ReadSpeed(int ID);// Прочитать скорость
	virtual int ReadLoad(int ID);// Прочитать нагрузку (процент напряжения на моторе 0~1000)
	virtual int ReadVoltage(int ID);// Прочитать напряжение
	virtual int ReadTemper(int ID);// Прочитать температуру
	virtual int ReadMove(int ID);// Прочитать состояние движения
	virtual int ReadCurrent(int ID);// Прочитать ток
protected:
	u8 Mem[SCSCL_PRESENT_CURRENT_H-SCSCL_PRESENT_POSITION_L+1];
};

#endif