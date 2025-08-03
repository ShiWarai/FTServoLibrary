"""
Python bindings for FTServo library using pybind11
"""
from __future__ import annotations
import typing
__all__ = ['SCSCL', 'SCSerial']
class SCSCL(SCSerial):
    def EnableTorque(self, ID: int, Enable: int) -> int:
        """
        Enable or disable torque for a servo
        """
    def FeedBack(self, ID: int) -> int:
        """
        Get feedback data from a servo
        """
    def LockEprom(self, ID: int) -> int:
        """
        Lock EPROM for a servo
        """
    def PWMMode(self, ID: int) -> int:
        """
        Enable PWM mode for a servo
        """
    def Ping(self, id: int) -> int:
        """
        Ping a servo by ID
        """
    def Read(self, ID: int, MemAddr: int, nData: int, nLen: int) -> int:
        """
        Read data from servo register
        """
    def ReadCurrent(self, ID: int) -> int:
        """
        Read current of a servo
        """
    def ReadLoad(self, ID: int) -> int:
        """
        Read load of a servo
        """
    def ReadMove(self, ID: int) -> int:
        """
        Read movement status of a servo
        """
    def ReadPos(self, ID: int) -> int:
        """
        Read position of a servo
        """
    def ReadSpeed(self, ID: int) -> int:
        """
        Read speed of a servo
        """
    def ReadTemper(self, ID: int) -> int:
        """
        Read temperature of a servo
        """
    def ReadVoltage(self, ID: int) -> int:
        """
        Read voltage of a servo
        """
    def RegWriteAction(self, ID: int = 254) -> int:
        """
        Execute registered write commands for a specific servo (default: 0xfe - all servos)
        """
    def RegWritePos(self, ID: int, Position: int, Time: int, Speed: int, Acc: int) -> int:
        """
        Register write position, time, speed, and acceleration for a single servo (requires RegWriteAction to activate)
        """
    def SyncWritePos(self, ids: list, positions: list, times: list, speeds: list, accs: list) -> None:
        """
        Synchronous write position for multiple servos
        """
    def WritePWM(self, ID: int, pwmOut: int) -> int:
        """
        Write PWM value for a servo
        """
    def WritePos(self, ID: int, Position: int, Time: int, Speed: int, Acc: int) -> int:
        """
        Write position, time, speed, and acceleration for a single servo
        """
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: int) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: int, arg1: int) -> None:
        ...
    def begin(self, baudrate: int, serial_port: str) -> bool:
        """
        Initialize the servo with baudrate and port
        """
    def end(self) -> None:
        """
        Close the servo connection
        """
    def genWrite(self, ID: int, MemAddr: int, nDat: int, nLen: int) -> int:
        """
        Write data to servo register
        """
    def readByte(self, ID: int, MemAddr: int) -> int:
        """
        Read one byte from servo register
        """
    def readWord(self, ID: int, MemAddr: int) -> int:
        """
        Read two bytes from servo register
        """
    def unLockEprom(self, ID: int) -> int:
        """
        Unlock EPROM for a servo
        """
    def writeByte(self, ID: int, MemAddr: int, bDat: int) -> int:
        """
        Write one byte to servo register
        """
    def writeWord(self, ID: int, MemAddr: int, wDat: int) -> int:
        """
        Write two bytes to servo register
        """
class SCSerial:
    def Ping(self, id: int) -> int:
        """
        Ping a servo by ID
        """
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: int) -> None:
        ...
    @typing.overload
    def __init__(self, arg0: int, arg1: int) -> None:
        ...
    def begin(self, baudrate: int, serial_port: str) -> bool:
        """
        Initialize the servo with baudrate and port
        """
    def end(self) -> None:
        """
        Close the servo connection
        """
    def getErr(self) -> int:
        """
        Get error code
        """
    def setBaudRate(self, baudrate: int) -> int:
        """
        Set baud rate
        """
    @property
    def IOTimeOut(self) -> int:
        """
        IO timeout in milliseconds
        """
    @IOTimeOut.setter
    def IOTimeOut(self, arg0: int) -> None:
        ...
