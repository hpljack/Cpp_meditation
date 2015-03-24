#ifndef FUNC2
#define FUNC2

#include <string>
using std::string;


inline const string& shortstring(const string& s1, const string& s2){
	return s1.size()> s2.size()? s1: s2;
}


void inlineFunctest();

bool lengthCompare(const string& s1, const string& s2);

//����ָ��
typedef bool(*cmpFcn)(const string&, const string&);//cmpFcn ��һ�ֺ���ָ�� bool func(string&,string&)
//����ָ�뵱���β�
/*
void useBigger(const string&, const string&,bool(const string&,const string&));
void useBigger(const string&,const string&, bool(*)(const string&,const string&));
*/

void funcPointertest();

#endif // !FUNC2
