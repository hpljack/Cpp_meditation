// chapter4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Thing{
public:
	Thing(const string& name,int cnt):m_name(name),m_cnt(cnt){}
	Thing():m_name("Hello"),m_cnt(0){}

	const string& getName(){
		return m_name;
	}
	int getCnt()const{      //记得适当的声明成员函数为const，确信成员函数不需要修改它的对象
		return m_cnt;
	}
	Thing(const Thing& t); //复制构造函数 （参数最好使用 const T& 不需要修改参数的值）
	Thing& operator=(const Thing& t);//赋值操作符（参数最好使用 const T& 不需要修改参数的值）
private:
	
	string m_name;
	int m_cnt;
};

Thing::Thing(const Thing& t){
	m_name = t.m_name;
	m_cnt = t.m_cnt;
}

Thing& Thing::operator=(const Thing& t){
	m_name = t.m_name;
	m_cnt = t.m_cnt;
	return *this;
}


class Complex{
public:
	Complex(int real, int img):m_real(real),m_img(img){}

	Complex(const Complex& c){
		m_real = c.m_real;
		m_img = c.m_img;
	}

	Complex& operator=(const Complex& c){
		m_real = c.m_real;
		m_img = c.m_img;
		return *this;
	}
	Complex operator+(const Complex& x){
		return Complex(m_real + x.m_real,m_img + x.m_img);
	}
	Complex operator-(const Complex& x){
		return Complex(m_real - x.m_real,m_img - x.m_img);
	}

	//int getReal()const{return m_real;}
	//int getImg()const{return m_img;}
	void printComplex(){
		cout<<m_real<<"+"<<m_img<<"j"<<endl;
	}
private:
	int m_real;
	int m_img;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Thing t("Jack",23);
	cout<<t.getName()<<" "<<t.getCnt()<<endl;

	Thing t2(t);//复制（拷贝）构造
	cout<<t2.getName()<<" "<<t2.getCnt()<<endl;

	Thing t3 = t; //制（拷贝）构造
	cout<<t3.getName()<<" "<<t3.getCnt()<<endl;

	Thing t4("brown",22);
	t = t4;//赋值操作符 operator=
	cout<<t.getName()<<" "<<t.getCnt()<<endl;

	Complex x(3,4);
	x.printComplex();

	Complex y(4,5);
	y.printComplex();

	Complex z = x + y;
	z.printComplex();
	
	cin.get();
	return 0;
}

