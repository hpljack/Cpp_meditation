#include "stdafx.h"
#include "func.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

void swap(int &v1, int &v2){
	if (v1 == v2){
		return;
	}
	return do_swap(v1,v2);
}

void do_swap(int &v1, int &v2){
	int temp = v1;
	v2 = v1;
	v1 = temp;
}
bool str_subrange(const string &str1, const string &str2){
	if (str1.size()== str2.size())
		return str1 == str2;
	string::size_type size = (str1.size()<str2.size())? str1.size():str2.size();
	for(string::size_type i = 0; i != size; ++i){
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

string make_plural(size_t ctr,const string &word,const string &ending){
	return (ctr == 1)? word: word + ending;//返回非引用类型 临时对象副本
}

const string &shorterString(const string &s1, const string &s2){
	return s1.size()< s2.size()? s1: s2; //返回引用类型
}

const string &manip(const string& s){
	/*
	string ret = s;
	return ret; */ //wrong: returning reference to a local object //会产生运行时错误
	return s;
}
//引用返回左值  就是可以给函数返回值赋值
char &get_val(string &str,string::size_type ix){
	return str[ix];
}

//修改为const 不能修改左值
const char &get_val(const string& str,string::size_type ix){
	return str[ix];
}

/*
  千万不要返回指向局部对象的指针
  一旦函数结束，局部对象被释放，返回的指针变成了垂悬指针
*/

//递归
int factorial_r(int val){
	if (val > 1)
		return factorial_r(val - 1) *val;
	return 1;
}

int factorial(int val){
	int result = 1;
	while(val > 1){
		result *= val;
		--val;
	}
	return result;
}

int rgcd(int v1, int v2){
	if (v2 != 0)
		return rgcd(v2, v1%v2);
	return v1;
}


//默认参数
string screenInit(string::size_type height = 24, string::size_type width = 80,char backgroud = ' '){
	//return "height=" + (height) + "width=" + string(width);
	return "default";
}

void func_test(){
	cout<<"***func_test***"<<endl;
	string s1 = "192.168.1.102";
	cout<<manip(s1)<<endl;

	string s2("some value");
	cout<<s2<<endl;
	get_val(s2,2) = 'A';
	cout<<s2<<endl;

	cout<<factorial(10)<<" " <<factorial(2)<<" "<< factorial(0)<<" "<<factorial(-1)<<endl;
	cout<<factorial_r(10)<<" " <<factorial_r(2)<<" "<< factorial_r(0)<<" "<<factorial_r(-1)<<endl;
	cout<<screenInit()<<endl;
}

