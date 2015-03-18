// chapter7.cpp : 定义控制台应用程序的入口点。
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

class UseCount{
public:
	UseCount();
	UseCount(const UseCount&);
	~UseCount();
	bool only();
	bool reattach(const UseCount&);
	bool makeonly();
private:
	int *p;
	UseCount& operator=(const UseCount&);
};

UseCount::UseCount():p(new int(1)){}
UseCount::UseCount(const UseCount& u):p(u.p){++*p;}
UseCount::~UseCount(){
	if(--*p == 0)
		delete p;
}
bool UseCount::only(){
	return *p == 1;
}
bool UseCount::reattach(const UseCount& u){
	++*u.p;
	if(--*p == 0){
		delete p;
		p = u.p;
		return true;
	}
	p = u.p;
	return false;
}
bool UseCount::makeonly(){
	if(*p == 1)
		return false;
	--*p;
	p = new int(1);
	return true;
}

class Handle{
public:
	Handle();
	Handle(int x, int y);
	Handle(const Point& p0);
	Handle(const Handle& h);
	Handle& operator=(const Handle& h);
	~Handle();
	int x()const;
	Handle& x(int xv);
	int y()const;
	Handle& y(int yv);
private:
	Point* p;
	UseCount u;  //纸箱引用计数的指针 使用缺省（默认）构造函数 
};
/*
Handle::Handle():u(new int(1)),p(new Point){}
Handle::Handle(int x, int y):u(new int(1)),p(new Point(x,y)){}
Handle::Handle(const Point& p0):u(new int(1)),p(new Point(p0)){}
Handle::Handle(const Handle& h):u(h.u),p(h.p){ ++*u; }
Handle& Handle::operator=(const Handle& h){
	++*h.u;
	if(--*u == 0){
		delete u;
		delete p;
	}
	u = h.u;
	p = h.p;
	return *this;
}

Handle::~Handle(){
	if(--*u == 0){
		delete u;
		delete p;
	}
}*/
//
// u使用缺省（默认）构造函数 
Handle::Handle():p(new Point()){}
Handle::Handle(int x, int y):p(new Point(x,y)){}
Handle::Handle(const Point& p0): p(new Point(p0)){}
Handle::Handle(const Handle& h): u(h.u),p(h.p){}
Handle::~Handle(){
	if(u.only())
		delete p;
}
Handle& Handle::operator=(const Handle& h){
	if(u.reattach(h.u))
		delete p;
	p = h.p;
	return *this;
}
int Handle::x()const{
	return p->x();
}
Handle& Handle::x(int xv){
	if(u.makeonly())
		p = new Point(*p);
	p->x(xv);
	return *this;
}
int Handle::y()const{
	return p->y();
}
Handle& Handle::y(int yv){
	if(u.makeonly())
		p = new Point(*p);
	p->y(yv);
	return *this;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Point pt(3,4);
	Handle h = pt;
	cout<<"pt="<<pt.x()<<" "<<pt.y()<<endl;
	cout<<"h="<<h.x()<<" "<<h.y()<<endl;

	pt.x(34);
	cout<<"pt="<<pt.x()<<" "<<pt.y()<<endl;
	cout<<"h="<<h.x()<<" "<<h.y()<<endl;
	
	Handle h2(pt);
	cout<<"h2="<<h2.x()<<" "<<h2.y()<<endl;

	cin.get();
	return 0;
}