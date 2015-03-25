// Hello.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Sales_item.h"

#include "Shape.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	std::cout<<"Enter two numbers:"<<std::endl;
	int v1, v2;
	std::cin>>v1>>v2;

	int lower, upper;
	if (v1<= v2){	
		lower = v1;
		upper = v2;
	}else{
		lower = v2;
		upper = v1;
	}

	int sum = 0;

	for(int i = lower; i <= upper; ++i)
		sum += i;

	std::cout<<"sum of "<< lower
		<<" to " <<upper
		<<" inclusive is "
		<< sum << std::endl;

	std::cout<<" endl" <<std::endl;
	*/


	cout<<"=================="<<endl;
	//int ival(1023);
	string all_nines(10,'9');

	cout<<all_nines<<endl;

	/*  
	** reference
	**
	*/
	int ival = 1024;
	int &refVal = ival;
	cout<<"refVal ="<<refVal<<endl;
	ival+=3;
	cout<<"refVal ="<<refVal<<endl;

	// const 引用
	const int i = 1024, i2 = 2048;
	const int &refi = i;

	const int &r = 10;
	//int &r2 = 10;//error : initializer must be an object
	double dval = 3.14;
	const int &ri = dval;


	/*
	** typedef 
	*/
	typedef double wages;
	typedef int exam_score;

	wages hourly, weekly;
	exam_score test_result;


	// enum 
	enum open_mode {input, output,append};
	enum Forms {shape = 1, sphere, cylinder, polygon};

	Sales_item book;


	std::cout<<"*************************"<<std::endl;
	CShape shape;


	cin.get();
	return 0;
}
