#include <iostream>
#include "SCServo.hpp"

SCSCL sc;

u8 ID[2] = {5, 6};
u16 Position[2];
u16 Speed[2];
u8 Acc[2];

int main(int argc, char **argv)
{
	if(argc<2){
        std::cout<<"argc error!"<<std::endl;
        return 0;
	}
	std::cout<<"serial:"<<argv[1]<<std::endl;
    if(!sc.begin(115200, argv[1])){
        std::cout<<"Failed to init scscl motor!"<<std::endl;
        return 0;
    }

	Speed[0] = 1;
	Speed[1] = 1;
	Acc[0] = 0;
	Acc[1] = 0;

	while(1){
		Position[0] = 500;
		Position[1] = 500;

		sc.SyncWritePos(ID, 2, Position, 0, Speed, Acc);
		std::cout<<"pos = "<<500<<std::endl;
		usleep(1000*1000);//[(P1-P0)/V]*1000+100
  
		Position[0] = 600;
		Position[1] = 600;

		sc.SyncWritePos(ID, 2, Position, 0, Speed, Acc);
		std::cout<<"pos = "<<600<<std::endl;
		usleep(1000*1000);//[(P1-P0)/V]*1000+100
	}
	sc.end();
	return 1;
}

