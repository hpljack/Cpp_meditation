#include "stdafx.h"
#include "iolib.h"
#include <iostream>


using std::cin;
using std::cerr;
using std::istream;
using std::ifstream;
using std::ofstream;

/*
  流状态测查询和控制
*/
void iostate_test(){
	int ival;
	while(std::cin>>ival,!std::cin.eof()){
		if(std::cin.bad()) //input stream is corrupted. bail out
			throw std::runtime_error("IO stream currupted");
		if (std::cin.fail()){ //bad input
			std::cerr<<"bad data, try again"; //warn the user
			cin.clear(istream::goodbit);//reset the stream
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');//ignore bad input
			continue;;
		}
		std::cout<<"ival="<<ival<<std::endl;
	}
}

void process_input(){

}
/*
	条件状态的访问
*/
void rdstate_test(){
	istream::iostate old_state = cin.rdstate();
	cin.clear();
	process_input();
	cin.clear(old_state);
}

void fstream_test(){
	std::string ifile("hello.txt");
	std::string ofile("world.txt");
	/*
	std::ifstream infile(ifile.c_str());
	std::ofstream oufile(ofile.c_str());

	infile.open("in");
	oufile.open("out");
	*/

}