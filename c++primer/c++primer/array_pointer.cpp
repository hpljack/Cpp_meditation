#include "stdafx.h"
#include "array_pointer.h"
#include <iostream>

using std::cout;
using std::endl;

void ArrayTest(){
	cout<<"*****ArrayTest***"<<endl;
	const size_t array_size = 10;
	int ia[array_size];
	for (size_t i = 0; i != array_size; ++i){
		ia[i] = i;
		cout<<ia[i]<<endl;
	}
}

void PointerTest(){
	cout<<"*****PointerTest****"<<endl;
	//ָ����
	string* sp1;
	string* sp2;

	int ival = 1024;
	int* pi = &ival;
	cout<<*pi<<endl;

	//void pointer
	double obj = 3.14;
	double* pd =&obj;
	void* pv = &obj; //void pointer can assigned by any type
	pv = pd;
	cout<<*pd<<endl;

	string s = "some value";
	sp1 = &s;//��ʼ��
	cout<<*sp1<<endl;
	*sp1 = "good bye";
	cout<<*sp1<<endl;

	//���ú�ָ�������
	int ival2 = 2048;
	int *pi1 = &ival2, *pi2 = &ival2;
	cout<<"pointer"<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;
	cout<<*pi1<<" "<<*pi2<<endl;
	pi1 = pi2;
	cout<<*pi1<<" "<<*pi2<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;

	//����
	int &ri1 = ival, &ri2= ival2;
	cout<<"reference"<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;
	cout<<ri1<<" "<<ri2<<endl;
	ri1 = ri2;
	cout<<ri1<<" "<<ri2<<endl;
	cout<<"ival="<<ival<<" "<<"ival2="<<ival2<<endl;

	//ָ��ָ���ָ�� ��Ӳ���
	//int *pi = &ival;
	int **ppi = &pi;

	cout<<"The value of ival"<<endl
		<<" Direct value: "<<ival<<endl
		<<" Indirect value : " <<*pi<<endl
		<<" Double indirect value: "<<**ppi<<endl;

	//use pointer acces array

	int ia[] = {0,2,4,8,10};
	int *ip = ia;
	int *last = ia + 4;
	int *last2 = ip + 4;
	cout<<*ip<<endl;
	cout<<*(ip+4)<<endl;
	cout<<*last2<<endl;
	cout<<*last<<endl;

	//ָ��������ĵ�����
	const size_t arr_sz = 5;
	int int_arr[arr_sz] = {0,1,2,3,4};
	for(int *pbegin = int_arr, *pend = int_arr + arr_sz; pbegin != pend; ++pbegin){
		cout<<*pbegin<<endl;
	}

	//ָ��const�����ָ�� ****�����޸�const�����ֵ****
	//1��ָ��const�����ָ�벻�ܸı�const�����ֵ ���Ը�ָ��Ҳ������const����
	//2��ָ��const�����ָ�����ָ���const����
	//3��ָ��const�����ָ�� ָ����Ƿ�const���� ���������������޸ķ�const����
	const double* cptr;
	const double PI = 3.14;
	cptr = &PI;
	//*cptr = 34; //errror ���ܸ�constָ�븳ֵ

	//double *ptr = &PI;//error const�������÷�constָ��
	double dval = 3.14;
	cptr = &dval;
		
	//constָ�� ***ָ�뱾���ֵ�����޸�***
	int errNumb = 0;
	int* const curErr = &errNumb;
	*curErr = 10;
	cout<<*curErr<<endl;
	//curErr = &ival; //error �����޸�ָ��

	//ָ��const�����constָ�� ****�Ȳ����޸�ָ����ָ���ֵ Ҳ�����޸�ָ�뱾��******
	const double * const pi_str = &PI;
	//pi_str = 43.4; //error
	//pi_str = &dval;//error

	//typedef ��ָ��
}