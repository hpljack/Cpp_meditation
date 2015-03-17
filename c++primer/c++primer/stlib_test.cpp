#include "stdafx.h"
#include "stlib_test.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype> //包含字符处理函数
#include <bitset>
#include "Sales_item.h"
//只使用必要的声明

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::bitset;

void stringTest(){
	cout<<"******stringTest*****"<<endl;
/*	string s;
	cin>>s;
	cout<<s<<endl;*/
	string st("The expense of spirit\n");
	string::size_type st_size = st.size(); //使用size_type 类型返回string的大小 是一种较为规范的写法
	cout<<"The size of "<< st <<" is" <<st_size
		<<" characters, including the newline"<<endl;

	string s1("hello, " );
	string s2("world");
	string s3 = s1 + s2;

	for(string::size_type i=0; i!= s3.size();++i){
		cout<<s3[i]<<endl;
	}

	//cctype中的函数
	string s("hello, World!@");
	string::size_type punct_cnt = 0;
	for (string::size_type i = 0; i != s.size(); ++i){
		if(ispunct(s[i]))
			++punct_cnt;
	}
	cout<<punct_cnt<<" punctuation characters in "<<s<<endl;

	for (string::size_type i=0; i != s.size(); ++i){
		s[i] = toupper(s[i]);
	}
	cout<<s<<endl;
}

void vectorTest(){
	cout<<"******vectorTest*****"<<endl;

	vector<int> ivec;
	vector<Sales_item> sales_vec;

	vector<int> fvec(10); //10 elements
	vector<string> svec(98);//10 elements

	cout<<fvec.size()<<endl;
	vector<string>::size_type ssieze = svec.size(); //使用vector<T>::size_type 不能使用vector::size_type
	cout<<ssieze<<endl;

	for (vector<int>::size_type i=0; i != fvec.size();++i){
		fvec[i] = i;
		cout<<"fvec["<<i<<"]="<<fvec[i]<<endl;
	}

	for (vector<int>::size_type i=0; i!=10;++i){
		ivec.push_back(i);
	}
}


void iteratorTest(){
	cout<<"******iteratorTest*****"<<endl;
	vector<int> ivec;
	for (vector<int>::size_type i=0; i!=10; ++i){
		ivec.push_back(i);
	}

	for (vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter){
		cout<<*iter<<endl;
		*iter *= 10;
	}

	//const_iterator
	for (vector<int>::const_iterator iter = ivec.begin(); iter!=ivec.end();++iter){
		cout<<*iter<<endl;
		//*iter += 1; //error const_iterator can not write
	}
}

void bitsetTest(){
	bitset<32> bitvect;
	bitset<16> bitvec1(0xffff);
	//use string init bitset
	string str("1100");
	bitset<32> bitvec4(str);
}