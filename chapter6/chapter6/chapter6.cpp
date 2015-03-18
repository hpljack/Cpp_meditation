// chapter6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Point{
public:
	Point():xval(0),yval(0){}
	Point(int x, int y):xval(x),yval(y){}
	int x()const{return xval;}
	int y()const{return yval;}
	Point& x(int xv){xval = xv; return *this;}
	Point& y(int yv){yval = yv; return *this;}
private:
	int xval,yval;
};
//前置声明
class UPoint;

//handle类 smart pointer 智能指针
class Handle{
public:
	Handle();
	Handle(int x, int y);
	Handle(const Point& p);
	Handle(const Handle& h);
	Handle& operator=(const Handle& h);
	~Handle();

	int x()const;
	Handle& x(int xv);
	int y()const;
	Handle& y(int yv);
private:
	UPoint* up;
};

class UPoint{
private: //所有成员都是私有成员
	friend class Handle;//友元 handle为Upoint的友元，所有可以访问Upoint的私有变量和私有成员函数
	Point p;
	int u;

	UPoint():u(1){}
	UPoint(int x, int y):p(x,y),u(1){}
	UPoint(const Point& p0):p(p0),u(1){}
};

Handle::Handle():up(new UPoint){}
Handle::Handle(int x, int y):up(new UPoint(x,y)){}
Handle::Handle(const Point& p):up(new UPoint(p)){}
Handle::~Handle(){ //如果发现引用计数=0 就删除Upoint对象
	if(--up->u == 0)
		delete up;
}
Handle::Handle(const Handle& h):up(h.up){++up->u;}
Handle& Handle::operator=(const Handle& h){
	++h.up->u;
	if(--up->u == 0)
		delete up;
	up = h.up;
	return *this;
}

int Handle::x()const{return up->p.x();}
int Handle::y()const{return up->p.y();}
//指针实现
/*
Handle& Handle::x(int xv){
	up->p.x(xv);
	return *this;
}
Handle& Handle::y(int yv){
	up->p.y(yv);
	return *this;
}
*/

//copy on write 写时复制 只有在绝对必要时才复制
//delphi中的string就是利用了该技术， 在写的时候产生副本，如果是读，多个对象指向相同的内存空间
Handle& Handle::x(int xv){
	if(up->u != 1){
		--up->u;
		up = new UPoint(up->p);
	}
	up->p.x(xv);
	return *this;
}

Handle& Handle::y(int yv){
	//如果引用计数为1，说明handle是唯一一个使用该Upoint对象的句柄
	//其他情况下复制Upoint对象
	if(up->u != 1){ 
		--up->u;
		up = new UPoint(up->p);
	}
	up->p.y(yv);
	return *this;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Point pt(3,4);
	cout<<pt.x()<<" "<<pt.y()<<endl;
	Point pt2 = pt.x(9);
	cout<<pt2.x()<<" "<<pt2.y()<<endl;
	cout<<pt.x()<<" "<<pt.y()<<endl;

	Handle h(3,4);
	Handle h2 = h;
	h2.x(5);
	int n = h.x(); //非写时复制
	cout<<n<<endl;
	h2.y(8);
	int m = h.y(); //写时复制 
	cout<<m<<endl;

	Handle h3 = pt;
	cout<<h3.x()<<" "<<h3.y()<<endl;
	pt.x(12);
	cout<<pt.x()<<" "<<pt.y()<<endl;
	cout<<h3.x()<<" "<<h3.y()<<endl;


	cin.get();
	return 0;
}

