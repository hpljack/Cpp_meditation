#ifndef FUNC2
#define FUNC2

#include <string>
using std::string;


inline const string& shortstring(const string& s1, const string& s2){
	return s1.size()> s2.size()? s1: s2;
}


void inlineFunctest();

bool lengthCompare(const string& s1, const string& s2);

//函数指针
typedef bool(*cmpFcn)(const string&, const string&);//cmpFcn 是一种函数指针 bool func(string&,string&)
//函数指针当做形参
/*
void useBigger(const string&, const string&,bool(const string&,const string&));
void useBigger(const string&,const string&, bool(*)(const string&,const string&));
*/

void funcPointertest();

#endif // !FUNC2
