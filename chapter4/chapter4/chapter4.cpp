// chapter4.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int getCnt()const{      //�ǵ��ʵ���������Ա����Ϊconst��ȷ�ų�Ա��������Ҫ�޸����Ķ���
		return m_cnt;
	}
	Thing(const Thing& t); //���ƹ��캯�� ���������ʹ�� const T& ����Ҫ�޸Ĳ�����ֵ��
	Thing& operator=(const Thing& t);//��ֵ���������������ʹ�� const T& ����Ҫ�޸Ĳ�����ֵ��
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

	Thing t2(t);//���ƣ�����������
	cout<<t2.getName()<<" "<<t2.getCnt()<<endl;

	Thing t3 = t; //�ƣ�����������
	cout<<t3.getName()<<" "<<t3.getCnt()<<endl;

	Thing t4("brown",22);
	t = t4;//��ֵ������ operator=
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

