#include "stdafx.h"
#include "Message.h"


Message::Message(const Message& m):contents(m.contents),folders(m.folders)
{
	put_Msg_in_Folder(folders);
}

void Message::put_Msg_in_Folder(const set<Folder*>& rhs){
	for(set<Folder*>::const_iterator beg = rhs.begin();
		beg != rhs.end();++beg)
		(*beg)->addMsg(this);
}
Message& Message::operator=(const Message& rhs){
	if(&rhs != this){
		remove_Msg_from_Folders();
		contents = rhs.contents;
		folders = rhs.folders;
		put_Msg_in_Folder(rhs.folders);
	}
	return *this;
}
void Message::remove_Msg_from_Folders(){
	for(set<Folder*>::const_iterator beg = folders.begin();
			beg != folders.end();++beg)
			(*beg)->remMsg(this);
}

Message::~Message()
{
	remove_Msg_from_Folders();
}

void Message::addFldr(Folder* f){
	folders.insert(f);
}

void Message::remFldr(Folder* f){
	folders.erase(f);
}

void Message::save(Folder& fldr){
	addFldr(&fldr);
	fldr.addMsg(this);
}

void Message::remove(Folder& fldr){
	remFldr(&fldr);
	fldr.remMsg(this);
}

//Folder
Folder::Folder(const Folder& f):messages(f.messages),folder_name(f.folder_name){
	put_Fldr_in_Message(f.messages);
}

void Folder::put_Fldr_in_Message(const set<Message*>& rhs){
	for(set<Message*>::const_iterator beg = rhs.begin();
			beg != rhs.end(); ++beg)
			(*beg)->addFldr(this);
}

void Folder::remove_Fldr_from_Message(){
	for (set<Message*>::const_iterator beg =messages.begin();
		 beg != messages.end(); ++beg)
		 (*beg)->remFldr(this);
}

Folder& Folder::operator=(const Folder& rhs){
	if(&rhs != this){
		messages = rhs.messages;
		folder_name = rhs.folder_name;
		put_Fldr_in_Message(messages);
	}
	return *this;
}

Folder::~Folder(){
	remove_Fldr_from_Message();
}

void Folder::save(Message& msg){
	addMsg(&msg);
	msg.addFldr(this);
}

void Folder::remove(Message& msg){
	remMsg(&msg);
	msg.remFldr(this);
}

void Folder::addMsg(Message* msg){
	messages.insert(msg);
}

void Folder::remMsg(Message* msg){
	messages.erase(msg);
}