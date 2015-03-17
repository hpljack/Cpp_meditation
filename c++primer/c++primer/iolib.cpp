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

	//�õ�������ʼ������
	vector<string> svec;
	list<string> slist(svec.begin(),svec.end());
	vector<string>::iterator mid = svec.begin() + svec.size()/2;
	vector<string> front(svec.begin(),mid);
	vector<string> back(mid,svec.end());

	//�����ʼ������
	char* words[] = {"stately","plump","buck","mulligan"};
	size_t word_size = sizeof(words)/sizeof(char*);
	list<string> words2(words,words+word_size);

	vector<Foo> empty;
	//vector<Foo> ok(10,"Hello");
	//����������
	vector<vector<string>> lines; //error
	vector< vector<string> > lines2;//ok >�����ÿո����

	list<int> ilist;
	for (size_t i = 0; i != 4; ++i)
	{
		ilist.push_back(i);
	}

	for (list<int>::iterator iter = ilist.begin(); iter != ilist.end();++iter){
		cout<<*iter<<endl;
	}

	//ָ��λ�ò���Ԫ��
	string spouse("Beth");
	slist.insert(slist.begin(),spouse);
	svec.insert(svec.begin(),spouse);

	//����һ��Ԫ��
	slist.insert(slist.begin(),words,words+2);


	//����Ԫ��
	if (!ilist.empty())
	{
		list<int>::reference val = *ilist.begin();
		list<int>::reference val2 = ilist.front();

		list<int>::reference last = *--ilist.end();
		list<int>::reference last2 = ilist.back();

	}

}