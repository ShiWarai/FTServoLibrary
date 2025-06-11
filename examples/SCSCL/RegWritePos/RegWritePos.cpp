/*
舵机出厂速度单位是0.0146rpm，速度为V=1500
*/

#include <iostream>
#include "SCServo.hpp"

SCSCL sc;

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
	while(1){
		sc.RegWritePos(5, 500, 0, 1, 0);// Пример: Acc=10
		sc.RegWritePos(6, 500, 0, 1, 0);// Пример: Acc=10
		sc.RegWriteAction();
		std::cout<<"pos = "<<500<<std::endl;
		usleep(750*1000);//[(P1-P0)/V]*1000+100
  
		sc.RegWritePos(5, 600, 0, 1, 0);// Пример: Acc=10
		sc.RegWritePos(6, 600, 0, 1, 0);// Пример: Acc=10
		sc.RegWriteAction();
		std::cout<<"pos = "<<600<<std::endl;
		usleep(750*1000);//[(P1-P0)/V]*1000+100
	}
	sc.end();
	return 1;
}

