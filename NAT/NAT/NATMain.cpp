#include <iostream>
#include "GetIpAddr.h"
#include "GetHostInfo.h"

using namespace std;


void main(){
	//GetIpAddr
	GetIpAddress();

	//gethostinfo
	GetGlobalData();

	cin.get();
	return;
}