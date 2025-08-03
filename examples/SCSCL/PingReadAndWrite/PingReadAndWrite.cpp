#include <iostream>
#include <vector>
#include <unistd.h>

#include "SCServo.hpp"

SCSCL sc;

int main(int argc, char **argv)
{
	if(argc < 3){
        std::cout << "Usage: " << argv[0] << " <serial_port> <servo_id_1> <servo_id_2>" << std::endl;
        return 1;
	}
	std::cout << "Serial port: " << argv[1] << std::endl;

    if(!sc.begin(115200, argv[1])){
        std::cout << "Failed to initialize SCSCL motor!" << std::endl;
        return 1;
    }

    u8 servo_id_1 = atoi(argv[2]);
    u8 servo_id_2 = atoi(argv[3]);
    int ping_id_1 = sc.Ping(servo_id_1);
    int ping_id_2 = sc.Ping(servo_id_2);

    if(ping_id_1 != -1){
        std::cout << "Ping successful for servo ID: " << ping_id_1 << std::endl;
    } else {
        std::cout << "Ping failed for servo ID: " << servo_id_1 << std::endl;
    }

    if(ping_id_2 != -1){
        std::cout << "Ping successful for servo ID: " << ping_id_2 << std::endl;
    } else {
        std::cout << "Ping failed for servo ID: " << servo_id_2 << std::endl;
    }

    if (ping_id_1 == -1 || ping_id_2 == -1) {
        std::cout << "Exiting due to failed ping." << std::endl;
        sc.end();
        return 1;
    }

    std::cout << "\nStarting cyclic movement and reading. Press Ctrl+C to stop." << std::endl;

    u8 IDs[2] = {servo_id_1, servo_id_2};
    u16 Positions[2];
    u16 Times[2] = {100, 100};
    u16 Speeds[2] = {0, 0};
    u8 Accs[2] = {0, 0};

    useconds_t pause_us = 75 * 1000;

	while(1)
    {
		Positions[0] = 500;
		Positions[1] = 500;
		sc.SyncWritePos(IDs, 2, Positions, Times, Speeds, Accs);
		std::cout << "SyncWritePos sent for position " << 500 << std::endl;

		usleep(pause_us);

        int current_pos_1 = sc.ReadPos(servo_id_1);
        int current_pos_2 = sc.ReadPos(servo_id_2);
        std::cout << "Servo " << servo_id_1 << " position: " << current_pos_1
                  << ", Servo " << servo_id_2 << " position: " << current_pos_2 << std::endl;


		Positions[0] = 600;
		Positions[1] = 600;
		sc.SyncWritePos(IDs, 2, Positions, Times, Speeds, Accs);
		std::cout << "SyncWritePos sent for position " << 600 << std::endl;

		usleep(pause_us);

        current_pos_1 = sc.ReadPos(servo_id_1);
        current_pos_2 = sc.ReadPos(servo_id_2);
        std::cout << "Servo " << servo_id_1 << " position: " << current_pos_1
                  << ", Servo " << servo_id_2 << " position: " << current_pos_2 << std::endl;
	}

	sc.end();
	return 0;
}
