#pragma once
#include <iostream>
#include <stdio.h>

class CShape //��״
{
public:
	CShape(void);
	virtual ~CShape(void);
private:
	int m_color;
public:
	void setColor(int color){m_color = color;}
};

class CRect: public CShape{ //����
public:
	void display(){std::cout<<"CRect"<<std::endl;}
};

class CEllipse: public CRect{//��Բ
public:
	void display(){std::cout<<"CEllipse"<<std::endl;}
};

class CTriangle: public CShape{//������
public:
	void display(){std::cout<<"CTriangle"<<std::endl;}
};

class CSquare: public CShape{//�ķ���
public:
	void display(){std::cout<<"CSquare"<<std::endl;}
};

class CCircle: public CEllipse{//Բ��
public:
	void display(){std::cout<<"CCircle"<<std::endl;}
};

