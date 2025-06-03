/*
舵机出厂速度单位是0.0146rpm，速度为V=1500
*/

#include <iostream>
#include "SCServo.hpp"

SCSCL sc;

int main(int argc, char **argv)
{
	if(argc<3){
        std::cout<<"argc error!"<<std::endl;
        return 0;
	}
	std::cout<<"serial:"<<argv[1]<<std::endl;
    if(!sc.begin(115200, argv[1])){
        std::cout<<"Failed to init scscl motor!"<<std::endl;
        return 0;
    }
	while(1){
		sc.WritePos(atoi(argv[2]), 500, 0, 0, 0);
		std::cout<<"pos = "<<500<<std::endl;
		usleep(75*1000);//[(P1-P0)/V]*1000+100
  
		sc.WritePos(atoi(argv[2]), 600, 0, 0, 0);
		std::cout<<"pos = "<<600<<std::endl;
		usleep(75*1000);//[(P1-P0)/V]*1000+100
	}
	sc.end();
	return 1;
}

