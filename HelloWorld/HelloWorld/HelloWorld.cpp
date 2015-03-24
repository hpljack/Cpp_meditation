// HelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include "Shape.h"
#include "Employee.h"

#include "ClassA.h"
#include "test.h"
#include "MyDoc.h"
#include "SavingAccount.h"
#include "Demo.h"
#include "graphicImage.h"
#include "Tree.h"

void CDemoTest(){
	cout<<"CDemoTest"<<endl;

	CDemo LocalObjectInFunc("LocalObjectInFunc");//in stack
	static CDemo StaticObject("StaticObject");//local static
	CDemo* pHeadObjectInFunc = new CDemo("HeapObjectInFunc");

	cout<<"Inside func "<<endl;
}

CDemo GlobalObject("GlobalObject");

/*
  template function sample
  *
*/
int power(int base,int exponent){
	int result = base;
	if (exponent == 0) return (int) 1;
	if (exponent < 0) return (int) 0;
	while (--exponent){
		result *= base;
	}
	return result;
}

long power1(int base,int exponent){
	long result = base;
	if (exponent == 0) return (long)1;
	if (exponent < 0) return (long)0;
	while(--exponent){
		result *= base;
	}
	return result;
}
template <class T>
T power(T base, T exponent){
	T result = base;
	if (exponent == 0) return (T) 1;
	if (exponent < 0) return (T) 0;
	while (--exponent){
		result *= base;
	}
	return result;
}
void templateTest(){
	cout<<"templateTest"<<endl;
	int i = power(5,4);
	long l = power(1000L,3);
	long double d = power((long double) 1e5,2);
	cout<<"i="<<i<<endl;
	cout<<"l="<<l<<endl;
	cout<<"d="<<d<<endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	std::cout<<"Hello world"<<std::endl;

	CSquare square;
	CRect rect1,rect2;
	CCirle circle;

	square.setColor(1);
	square.display();
	rect1.display();
	rect2.display();
	circle.display();
	

	//
	CManager aManager("������");
	CSales aSales("���");
	CWage aWager("����Դ");
	std::cout<<aWager.getName()<<"�Ĺ��ʣ�"<<aWager.computePay()<<std::endl;
		
	aWager = aSales;
	std::cout<<aWager.getName()<<"�Ĺ��ʣ�"<<aWager.computePay()<<std::endl;

	//aSales = aWager;

	CWage* pWager;
	CSales* pSales;

	pWager = &aWager;
	pSales = &aSales;
	pWager = &aSales;
	pSales = (CSales*)pWager;

	std::cout<<"*******************"<<std::endl;
	CEmployee* pEmployee;
	pEmployee = &aWager;
	std::cout<<pEmployee->getName()<<"�Ĺ��ʣ�"<<pEmployee->computePay()<<std::endl;
	pEmployee = &aSales;
	std::cout<<pEmployee->getName()<<"�Ĺ��ʣ�"<<pEmployee->computePay()<<std::endl;
	pEmployee = &aManager;
	std::cout<<pEmployee->getName()<<"�Ĺ��ʣ�"<<pEmployee->computePay()<<std::endl;

	pSales = &aSales;
	pWager = &aSales;
	std::cout<<pSales->getName()<<"�Ĺ��ʣ�"<<pSales->computePay()<<std::endl;
	std::cout<<pWager->getName()<<"�Ĺ��ʣ�"<<pWager->computePay()<<std::endl;


	CShape* pShape;
	CEllipse aEllipse;
	CCirle aCirle;
	CTriangle aTriangle;
	CRect aRect;

	pShape = &aCirle;

	CShape* pShape1[5] = {pShape,&aEllipse,&aCirle,&aTriangle,&aRect};
	for (int i = 0; i < 5; ++i){
		pShape1[i]->display();
	}
	
	//����ClassA
	ClassATest();

	//����Test
	//TestStructLength();


	//����CMyDoc
	CMyDocTest();

	//��������
	TestSavingAccount();
	
	//CDemo����
	CDemo LocalObjectInMain("LocalObjectInMain");
	CDemo* pHeadObjectInMain = new CDemo("HeadObjectInMain");
	cout<<"In main, before calling CDemotest"<<endl;
	CDemoTest();
	cout<<"In main, after calling CDemoTest"<<endl;
	//RTTI ����
	TypeInfoTest();
	//template ����
	templateTest();
	tempalateClassTest();

	//ͣ����ʾ
	std::cin.get();
	return 0;
}

