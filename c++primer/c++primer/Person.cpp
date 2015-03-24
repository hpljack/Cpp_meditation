#include "stdafx.h"
#include "Person.h"



Person::~Person()
{
}

char Screen::get(index ht,index wd)const{
	//Screen::index  row = ht * width;
	//return contents[row + wd];

	return contents[ht];
}

inline Screen::index Screen::get_cursor()const{
	return cursor;
}

Screen& Screen::set(char c){
	contents[cursor] = c;
	return *this;
}

Screen& Screen::move(index c,index r){
	index row = r * width;
	cursor = row + c;
	return *this;
}

Window_Mgr& Window_Mgr::relocate(Screen::index r, Screen::index c,Screen& s){
	s.height += r;
	s.width += c;
	return *this;
}