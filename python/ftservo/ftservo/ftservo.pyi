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
    def RegWritePos(self, ID: int, Position: int, Time: int, Speed: int, Acc: int) -> int:
        """
        Register write position, time, speed, and acceleration for a single servo (requires RegWriteAction to activate)
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
    def sync_write_pos(self, ids: list, positions: list, times: list, speeds: list, accs: list) -> None:
        """
        Synchronous write position for multiple servos
        """
    def unLockEprom(self, ID: int) -> int:
        """
        Unlock EPROM for a servo
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
