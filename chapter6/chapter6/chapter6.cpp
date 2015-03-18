// chapter6.cpp : �������̨Ӧ�ó������ڵ㡣
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
//ǰ������
class UPoint;

//handle�� smart pointer ����ָ��
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
private: //���г�Ա����˽�г�Ա
	friend class Handle;//��Ԫ handleΪUpoint����Ԫ�����п��Է���Upoint��˽�б�����˽�г�Ա����
	Point p;
	int u;

	UPoint():u(1){}
	UPoint(int x, int y):p(x,y),u(1){}
	UPoint(const Point& p0):p(p0),u(1){}
};

Handle::Handle():up(new UPoint){}
Handle::Handle(int x, int y):up(new UPoint(x,y)){}
Handle::Handle(const Point& p):up(new UPoint(p)){}
Handle::~Handle(){ //����������ü���=0 ��ɾ��Upoint����
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
//ָ��ʵ��
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

//copy on write дʱ���� ֻ���ھ��Ա�Ҫʱ�Ÿ���
//delphi�е�string���������˸ü����� ��д��ʱ���������������Ƕ����������ָ����ͬ���ڴ�ռ�
Handle& Handle::x(int xv){
	if(up->u != 1){
		--up->u;
		up = new UPoint(up->p);
	}
	up->p.x(xv);
	return *this;
}

Handle& Handle::y(int yv){
	//������ü���Ϊ1��˵��handle��Ψһһ��ʹ�ø�Upoint����ľ��
	//��������¸���Upoint����
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
	int n = h.x(); //��дʱ����
	cout<<n<<endl;
	h2.y(8);
	int m = h.y(); //дʱ���� 
	cout<<m<<endl;

	Handle h3 = pt;
	cout<<h3.x()<<" "<<h3.y()<<endl;
	pt.x(12);
	cout<<pt.x()<<" "<<pt.y()<<endl;
	cout<<h3.x()<<" "<<h3.y()<<endl;


	cin.get();
	return 0;
}

