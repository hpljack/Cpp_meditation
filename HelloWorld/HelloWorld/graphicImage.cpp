#include "stdafx.h"
#include "graphicImage.h"
#include <typeinfo.h>

graphicImage::~graphicImage(){

}

void processFileRTTI(graphicImage *atype){
	if(typeid(GIFImage) == typeid(*atype)){
		((GIFImage*)atype)->display();
	}else if (typeid(PICImage) == typeid(*atype)){
		((PICImage*)atype)->display();
	}else
	{
		cout<<"Unkonw type!"<<(typeid(*atype).name())<<endl;
	}
}

void TypeInfoTest(){
	cout<<"****TypeInfoTest*****"<<endl;
	graphicImage* gImage = new GIFImage();
	graphicImage* pImage = new PICImage();

	processFileRTTI(gImage);
	processFileRTTI(pImage);
}