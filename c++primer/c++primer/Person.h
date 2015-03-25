#ifndef PERSON_H //ʹ��ͷ�ļ�����
#define PERSON_H

#include <string>
using namespace std;

#pragma once

class Person
{
private:
	string m_name;
	string m_addr;
public:
	Person(const string& name,const string& addr){
		m_name = name;
		m_addr = addr;
	}
	~Person();
	const string& Name(){return m_name;}
	const string& Addr(){return m_addr;}
};

class Window_Mgr;
class Screen{
public:
	typedef string::size_type index;
	//overload function
	//implicitly inline when defined inside the class declaration
	char get()const{return contents[cursor];}
	//explicitly declared as inline, will be defined outside the class declaration
	char get(index ht,index wd)const;
	//�������get������Ϊinline ���������
	index get_cursor()const;
	Screen(const string& contents):acces_ctr(0){
		this->contents = contents;
		cursor = 0;
		width = this->contents.length() * 5;
		height = 20;
	}
	Screen():acces_ctr(0){
		contents = "Hello Screen";
		cursor = 0;
		width = contents.length() * 5;
		height = 20;
	}
	Screen(const string& content,int nheight):contents(content),height(nheight){
		cursor = 0;
		width = contents.length() * 5;
	}

	Screen& move(index c,index r);
	Screen& set(char);
	Screen& set(index,index,char);

	//����const �ͷ�constҲ��������
	Screen& display(std::ostream& os){
		do_display(os);
		return *this;
	}
	const Screen& display(std::ostream& os)const{
		do_display(os);
		return *this;
	}
private:
	void do_display(std::ostream&os)const{
		++acces_ctr;
		os<<contents<<"\t"<<width<<"\t"<<height;
	}
	string contents;
	string::size_type cursor;
	string::size_type height,width;
	//�ɱ����ݳ�Ա
	mutable size_t acces_ctr;

	friend class Window_Mgr;//��Ԫ ���Է��ʸ����˽�г�Ա�ͳ�Ա����
		//Window_Mgr::relocate(Window_Mgr::index,Window_Mgr::index,Screen&);
};


class Window_Mgr{
private:
	typedef size_t index;
public:
	Window_Mgr& relocate(Screen::index r, Screen::index c,Screen& s);
};

#endif // !PERSON_H