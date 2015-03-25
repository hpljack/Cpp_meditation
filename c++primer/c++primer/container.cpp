#include "stdafx.h"
#include "contianer.h"
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

void initContainer(){
	cout<<"***initContainer***"<<endl;
	vector<int> ivec;
	vector<int> ivec2(ivec);
	vector<string> svec;

	//使用迭代器复制容器
	list<string> slist(svec.begin(),svec.end());
	vector<string>::iterator mid = svec.begin() + svec.size() / 2;
	deque<string> front(svec.begin(),mid);
	deque<string> back(mid,svec.end());


}