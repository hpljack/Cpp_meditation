// Chapter0.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>

class Trace{
public:
	Trace(){noisy = 0;}
	Trace(FILE* ff){noisy = 0; f = ff;}
	void print(char* s){
		//if(noisy) printf("%s",s);
		if(noisy) fprintf(f,"%s",s);
	}
	// 由于on（） off（）定义在C++类内部，会议inline展开
	void on(){noisy = 1;}
	void off(){noisy = 0;}
private:
	int noisy;
	FILE* f;
};


int _tmain(int argc, _TCHAR* argv[])
{
	Trace t;
	t.on();
	t.print("begin main()\n");
	t.print("end main()\n");

	Trace t2(stderr);
	t2.on();
	t2.print("t2 begin main\n");
	t2.print("t2 end main\n");


	std::cin.get();
	return 0;
}

