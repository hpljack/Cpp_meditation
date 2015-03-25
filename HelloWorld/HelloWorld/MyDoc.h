#pragma once

class CObject{
public:
	virtual void Serializee(){cout<<"CObject::serialize()"<<endl;}
};
class CDocument: public CObject{
public:
	int m_data1;
	void func(){
		cout<<"CDocument::func()"<<endl;
		Serializee();
	}
	virtual void Serializee(){cout<<"CDocument::serialize()"<<endl;}
};
class CMyDoc: public CDocument
{
public: 
	int m_data2;
	virtual void Serializee(){cout<<"CMyDoc::serialize()"<<endl;}
public:
	CMyDoc(void);
	~CMyDoc(void);
};

void CMyDocTest();