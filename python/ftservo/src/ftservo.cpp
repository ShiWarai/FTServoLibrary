#include <pybind11/pybind11.h>
#include "SCSerial.hpp"
#include "SCSCL.hpp" // Предполагаемый заголовочный файл для SCSCL

namespace py = pybind11;

// Функция для инициализации Python-модуля
PYBIND11_MODULE(ftservo, m) {
    m.doc() = "Python bindings for FTServo library using pybind11";

    // Базовый класс SCSerial
    py::class_<SCSerial>(m, "SCSerial")
        .def(py::init<>()) // Конструктор по умолчанию
        .def(py::init<u8>()) // Конструктор с параметром End
        .def(py::init<u8, u8>()) // Конструктор с параметрами End и Level
        .def("begin", &SCSerial::begin, "Initialize the servo with baudrate and port",
             py::arg("baudrate"), py::arg("serial_port"))
        .def("Ping", &SCSerial::Ping, "Ping a servo by ID", py::arg("id"))
        .def("end", &SCSerial::end, "Close the servo connection")
        .def("getErr", &SCSerial::getErr, "Get error code")
        .def("setBaudRate", &SCSerial::setBaudRate, "Set baud rate", py::arg("baudrate"))
        .def_readwrite("IOTimeOut", &SCSerial::IOTimeOut, "IO timeout in milliseconds");

    // Класс SCSCL, наследующий от SCSerial
    py::class_<SCSCL, SCSerial>(m, "SCSCL")
        .def(py::init<>()) // Конструктор по умолчанию
        .def(py::init<u8>()) // Конструктор с параметром End
        .def(py::init<u8, u8>()) // Конструктор с параметрами End и Level
        // Наследуем базовые методы
        .def("begin", &SCSCL::begin, "Initialize the servo with baudrate and port",
             py::arg("baudrate"), py::arg("serial_port"))
        .def("Ping", &SCSCL::Ping, "Ping a servo by ID", py::arg("id"))
        .def("end", &SCSCL::end, "Close the servo connection")
        // Добавляем специфичные методы SCSCL
        .def("genWrite", &SCSCL::genWrite, "Write data to servo register",
             py::arg("ID"), py::arg("MemAddr"), py::arg("nDat"), py::arg("nLen"))
        .def("Read", &SCSCL::Read, "Read data from servo register",
             py::arg("ID"), py::arg("MemAddr"), py::arg("nData"), py::arg("nLen"))
        .def("writeByte", &SCSCL::writeByte, "Write one byte to servo register",
             py::arg("ID"), py::arg("MemAddr"), py::arg("bDat"))
        .def("writeWord", &SCSCL::writeWord, "Write two bytes to servo register",
             py::arg("ID"), py::arg("MemAddr"), py::arg("wDat"))
        .def("readByte", &SCSCL::readByte, "Read one byte from servo register",
             py::arg("ID"), py::arg("MemAddr"))
        .def("readWord", &SCSCL::readWord, "Read two bytes from servo register",
             py::arg("ID"), py::arg("MemAddr"))
        .def("WritePos", &SCSCL::WritePos,
             "Write position, time, speed, and acceleration for a single servo",
             py::arg("ID"), py::arg("Position"), py::arg("Time"), py::arg("Speed"), py::arg("Acc"))
        .def("RegWritePos", &SCSCL::RegWritePos,
             "Register write position, time, speed, and acceleration for a single servo (requires RegWriteAction to activate)",
             py::arg("ID"), py::arg("Position"), py::arg("Time"), py::arg("Speed"), py::arg("Acc"))
        .def("RegWriteAction", &SCSCL::RegWriteAction,
             "Execute registered write commands for a specific servo (default: 0xfe - all servos)",
             py::arg("ID") = 0xfe)
        .def("SyncWritePos", [](SCSCL& self, py::list ids, py::list positions, py::list times, py::list speeds, py::list accs) {
            size_t n = ids.size();
            if (positions.size() != n || times.size() != n || speeds.size() != n || accs.size() != n) {
                throw pybind11::value_error("All input lists for SyncWritePos must have the same size");
            }

            if (n == 0) {
                return;
            }

            std::vector<u8> id_vec(n);
            std::vector<u16> pos_vec(n);
            std::vector<u16> time_vec(n);
            std::vector<u16> speed_vec(n);
            std::vector<u8> acc_vec(n);

            for (size_t i = 0; i < n; ++i) {
                try {
                    id_vec[i] = ids[i].cast<u8>();
                    pos_vec[i] = positions[i].cast<u16>();
                    time_vec[i] = times[i].cast<u16>();
                    speed_vec[i] = speeds[i].cast<u16>();
                    acc_vec[i] = accs[i].cast<u8>();
                } catch (const pybind11::cast_error& e) {
                    throw pybind11::type_error("Invalid type in one of the lists: " + std::string(e.what()));
                } catch (const pybind11::value_error& e) {
                    throw pybind11::value_error("Value out of range for type (u8 or u16): " + std::string(e.what()));
                }
            }

            self.SyncWritePos(id_vec.data(), n, pos_vec.data(), time_vec.data(), speed_vec.data(), acc_vec.data());
        }, "Synchronous write position for multiple servos",
        py::arg("ids"), py::arg("positions"), py::arg("times"), py::arg("speeds"), py::arg("accs"))
        .def("PWMMode", &SCSCL::PWMMode, "Enable PWM mode for a servo", py::arg("ID"))
        .def("WritePWM", &SCSCL::WritePWM, "Write PWM value for a servo", py::arg("ID"), py::arg("pwmOut"))
        .def("EnableTorque", &SCSCL::EnableTorque, "Enable or disable torque for a servo", py::arg("ID"), py::arg("Enable"))
        .def("unLockEprom", &SCSCL::unLockEprom, "Unlock EPROM for a servo", py::arg("ID"))
        .def("LockEprom", &SCSCL::LockEprom, "Lock EPROM for a servo", py::arg("ID"))
        .def("FeedBack", &SCSCL::FeedBack, "Get feedback data from a servo", py::arg("ID"))
        .def("ReadPos", &SCSCL::ReadPos, "Read position of a servo", py::arg("ID"))
        .def("ReadSpeed", &SCSCL::ReadSpeed, "Read speed of a servo", py::arg("ID"))
        .def("ReadLoad", &SCSCL::ReadLoad, "Read load of a servo", py::arg("ID"))
        .def("ReadVoltage", &SCSCL::ReadVoltage, "Read voltage of a servo", py::arg("ID"))
        .def("ReadTemper", &SCSCL::ReadTemper, "Read temperature of a servo", py::arg("ID"))
        .def("ReadMove", &SCSCL::ReadMove, "Read movement status of a servo", py::arg("ID"))
        .def("ReadCurrent", &SCSCL::ReadCurrent, "Read current of a servo", py::arg("ID"));
}