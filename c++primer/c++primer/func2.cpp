#include "stdafx.h"
#include "func2.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;



const string& shortString(const string& s1, const string& s2){
	return s1.size() > s1.size()? s2: s1;
}

bool lengthCompare(const string& s1, const string& s2){
	int op = 0;
	switch (op)
	{
	case 0:
		return s1.size() > s2.size();
	case 1:
		return s1.size() == s2.size();
	case 2:
		return s1.size() < s1.size();
	default:
		return false;
		break;
	}
}

void inlineFunctest(){
	const string s1("nihao");
	const string s2("Hellowolrd");
	cout<<shortstring(s1,s2)<<endl;
	cout<<shortString(s1,s2)<<endl;
}

void funcPointertest(){
	cout<<"****funcPointertest***"<<endl;
	cmpFcn pf1 = NULL;
	cmpFcn pf2 = lengthCompare;

	string s1("Good morning");
	string s2("con ni chi wa");
	//(*pf2)(s1,s2);
	if (pf2(s1,s2)) {
		cout<<s1<<" are equal to "<<s2<<endl;
	}else{

		cout<<s1<<" are not equal to "<<s2<<endl;
	}

}