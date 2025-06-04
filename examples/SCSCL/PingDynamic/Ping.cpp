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
	
	int ID = sc.Ping(atoi(argv[2]));
	if(ID!=-1){
		std::cout<<"ID:"<<ID<<std::endl;
	}else{
		std::cout<<"Ping servo ID error!"<<std::endl;
	}
	sc.end();
	return 1;
} 