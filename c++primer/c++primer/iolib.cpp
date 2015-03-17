#include "stdafx.h"
#include "iolib.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "foo.h"
#include <string>

using namespace std;

void InitContainer_test(){
	cout<<"***InitContainer_test***"<<endl;
	vector<int> ivec;
	vector<int> ivec2(ivec);
	//list<int> ilist(ivec);

	//用迭代器初始化容器
	vector<string> svec;
	list<string> slist(svec.begin(),svec.end());
	vector<string>::iterator mid = svec.begin() + svec.size()/2;
	vector<string> front(svec.begin(),mid);
	vector<string> back(mid,svec.end());

	//数组初始化容器
	char* words[] = {"stately","plump","buck","mulligan"};
	size_t word_size = sizeof(words)/sizeof(char*);
	list<string> words2(words,words+word_size);

	vector<Foo> empty;
	//vector<Foo> ok(10,"Hello");
	//容器的容器
	vector<vector<string>> lines; //error
	vector< vector<string> > lines2;//ok >必须用空格隔开

	list<int> ilist;
	for (size_t i = 0; i != 4; ++i)
	{
		ilist.push_back(i);
	}

	for (list<int>::iterator iter = ilist.begin(); iter != ilist.end();++iter){
		cout<<*iter<<endl;
	}

	//指定位置插入元素
	string spouse("Beth");
	slist.insert(slist.begin(),spouse);
	svec.insert(svec.begin(),spouse);

	//插入一段元素
	slist.insert(slist.begin(),words,words+2);


	//访问元素
	if (!ilist.empty())
	{
		list<int>::reference val = *ilist.begin();
		list<int>::reference val2 = ilist.front();

		list<int>::reference last = *--ilist.end();
		list<int>::reference last2 = ilist.back();

	}

}