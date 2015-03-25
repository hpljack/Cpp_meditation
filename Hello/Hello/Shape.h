#pragma once
#include <iostream>
#include <stdio.h>

class CShape //形状
{
public:
	CShape(void);
	virtual ~CShape(void);
private:
	int m_color;
public:
	void setColor(int color){m_color = color;}
};

class CRect: public CShape{ //矩形
public:
	void display(){std::cout<<"CRect"<<std::endl;}
};

class CEllipse: public CRect{//椭圆
public:
	void display(){std::cout<<"CEllipse"<<std::endl;}
};

class CTriangle: public CShape{//三角形
public:
	void display(){std::cout<<"CTriangle"<<std::endl;}
};

class CSquare: public CShape{//四方形
public:
	void display(){std::cout<<"CSquare"<<std::endl;}
};

class CCircle: public CEllipse{//圆形
public:
	void display(){std::cout<<"CCircle"<<std::endl;}
};

