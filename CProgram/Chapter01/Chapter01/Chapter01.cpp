// Chapter01.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

void Endl(){ //����
	cin.get();
}

/*
 *�ằ����ʧ��
 */

void c011test(void){
	double t, s, v, h;
	int n;
	printf("���������");
	scanf("%d",&n); //�������
	t = 1;
	s = 1;
	//for(int i = 2; i <= n; i++){ //Ӧ���� ��= ��������<= 
	for(int i = 2; i != n; i++){
		t *= 2;
		s += t;
	}
	v = s / 1.42e8;
	h = v * 9 / 3.1415926;
	h = pow(h,1.0/3);

	printf(" ��������ԼΪ�� %.3e\n",s);
	printf(" �ۺ����ԼΪ�� %.0f������\n",v);
	printf(" ��Բ׶��Ѹ�ԼΪ�� %.0f��\n",h);

	Endl();
}
/*
 * ����
 */
void c012test(){
	
	double t, s;
	int n;
	printf("������n:");
	scanf("%d",&n);
	t = 1;
	s = 1;
	for(int i = 2; i != n; i++){
		t *= 2;
		s += t;
	}
	printf(" �ܹ���Ҫ���� %.4f ¬����", s / 400); //�����¬�����

	Endl();
}
/*
 * ��������ʽ
 *  n < 1 + 1/2 + 1/3 +...+1/m < n + 1
 * �����ͼ�������ʽ
 */
void c021(){
	long c, d, i, n;
	double s;
	cout<<"��  n < 1 + 1/2 + 1/3 +...+1/m < n + 1������m."<<endl;
	cout<<"������n: ";
	cin>>n;
	i = 0;
	s = 0;
	while(s < n){ //������������
		i += 1;
		s += 1.0/i;
	}
	c = i;
	while(s < n + 1){//������������
		i += 1;
		s += 1.0/i;
	}
	d = i - 1;

	cout<<endl<<"���㲻��ʽ��mΪ: "<<c <<" <= m <= "<< d <<endl;

	Endl();
}

/*
 * �ⲻ��ʽ d< 1+ 1/2 - 1/3 + 1/4 - 1/5+...+-1/m �Ľ�
 */
void c022(){
	long d, m , k;
	double s;
	cout<<"������d:";
	cin>>d;
	cout<<endl<<" d <1+1/2-1/3+1/4-1/5...1+-1/m�Ľ�:"<<endl;
	m = 1;
	s = 1;
	while(true){
		s = s + 1.0/m + 1.0/(m+1) -1.0/(m+2);
		if(s < d)
			break;
		m += 3;
	}
	cout<<"m>="<<m<<endl; //�����
	k = 1;
	s = 0;
	while(k < m){
		if(k%3 > 0){
			s += 1.0/k;
		}else{
			s -= 1.0/k;
		}
		if (s > d)
			cout<<"m="<<m; //һ����ɢ��
		k++;
	}

	Endl();

}

/*
 * ��n�Ľ׳�n��
 */
void c031(){
	int n;
	cout<<"������n��"<<endl;
	cin>>n;
	int t = 1;
	for(int i = 1; i <= n; i++){
		t *= i;
	}
	cout<<n<<"!= "<<t<<endl;

	Endl();
}
//�ݹ���n�Ľ׳�n��
long fac(int n){
	long f;
	if(n == 1) 
		f = 1;
	else
		f = n * fac(n - 1);
	return f;
}
void c032(){
	int n;
	cout<<"������n��"<<endl;
	cin>>n;
	long y = fac(n);
	cout<<n<<"!= "<<y<<endl;
	Endl();
}

/*
 *ѡ�����������A(n,m) �������C(n,m)
 */
void c033(){

}

long factorial(int n){
	if (n == 1)
		return 1;
	long f = 1;
	for(int i = 1; i <= n; i++)
		f *= i;
	return f;
}

// abc = a��+b��+c��
void c034(){

	int m, n;
	cout<<"��λ�׳˺�����:";
	for(int a = 1; a <= 6; a++){
		for(int b = 0; b <= 6; b++){
			for(int c = 0; c <= 6; c++){
				m = a * 100 + b * 10 +c;
				n = factorial(a) + factorial(b) + factorial(c);
				if(m == n)
					cout<<m<<endl;
			}
		}
	}
	Endl();
}

int _tmain(int argc, _TCHAR* argv[])
{

	//c011test();
	//c012test();
	//c021();
	//c022();
	//c031();
	//c032();
	c034();

	//cin.get();
	return 0;
}


