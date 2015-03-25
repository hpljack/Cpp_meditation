#ifndef MESSAGE_H
#define MESSAGE_H
#pragma once
#include <string>
#include <iostream>
#include <set>

using namespace std;

class Message;

class Folder{
public:
	Folder(const string& s):folder_name(s){}
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

	void save(Message&);
	void remove(Message&);

	void addMsg(Message*);
	void remMsg(Message*);
private:
	set<Message*> messages;
	string folder_name;

	void put_Fldr_in_Message(const set<Message*>&);
	void remove_Fldr_from_Message();
};

class Message
{
public:
	Message(const string& str=""):contents(str){}
	Message(const Message&);//复制构造函数
	Message& operator=(const Message&);//赋值操作符
	~Message();

	void save(Folder&);
	void remove(Folder&);

	void addFldr(Folder*);
	void remFldr(Folder*);
private:
	string contents; //actual message text
	set<Folder*> folders;//folders that have this message
	void put_Msg_in_Folder(const set<Folder*>&);
	void remove_Msg_from_Folders();
};


#endif // !MESSAGE_H

