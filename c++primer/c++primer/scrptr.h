#ifndef SCRPTR_H
#define SCRPTR_H
#include "Person.h"
#include <iostream>

class ScrPtr{
	friend class ScreenPtr;
	Screen *sp;
	size_t use;
	ScrPtr(Screen *p):sp(p),use(1){}
	~ScrPtr(){delete sp;}
};

class ScreenPtr{
public:
	ScreenPtr(Screen* p):ptr(new ScrPtr(p)){}
	ScreenPtr(const ScreenPtr& orig):ptr(orig.ptr){++ptr->use;}
	ScreenPtr& operator=(const ScreenPtr&);
	~ScreenPtr(){
		if(--ptr->use = 0)
			delete ptr;
	}
	//两个版本 const和非const
	Screen& operator*(){return *ptr->sp;}
	Screen* operator->(){return ptr->sp;}
	const Screen& operator*()const{return *ptr->sp;}
	const Screen* operator->()const{return ptr->sp;}
private:
	ScrPtr *ptr;
};

ScreenPtr& ScreenPtr::operator=(const ScreenPtr& rhs){
	++rhs.ptr->use;
	if(--ptr->use == 0)
		delete ptr;
	ptr = rhs.ptr;
	return *this;//注意赋值 复合赋值操作符必须返回*this
}

void scrptrTest(){
	Screen myscreen("override * -> operator",28);
	ScreenPtr p(&myscreen);
	p->display(std::cout);
}


#endif // !SCRPTR_H
