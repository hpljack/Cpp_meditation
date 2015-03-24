#pragma once
class graphicImage
{
public:
	graphicImage(){strcpy(name,"graphicImage");}
	~graphicImage(void);
protected:
	char name[80];
public:
	virtual void display(){
		cout<<"Display a generic image"<<endl;
	}
	char* getName(){
		return name;
	}
};

class GIFImage: public graphicImage{
public:
	GIFImage(){strcpy(name,"GIFImage");}
	void display(){
		cout<<"Display a GIF file"<<endl;
	}
};

class PICImage: public graphicImage{
public:
	PICImage(){strcpy(name,"PICImage");}
	void display(){
		cout<<"Display a PIC File "<<endl;
	}
};

void processFileRTTI(graphicImage *atype);
void TypeInfoTest();