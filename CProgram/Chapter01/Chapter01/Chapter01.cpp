// Chapter01.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

void Endl(){ //结束
	cin.get();
}

/*
 *舍罕王的失算
 */

void c011test(void){
	double t, s, v, h;
	int n;
	printf("输入格数：");
	scanf("%d",&n); //输入格数
	t = 1;
	s = 1;
	//for(int i = 2; i <= n; i++){ //应该用 ！= ，而不是<= 
	for(int i = 2; i != n; i++){
		t *= 2;
		s += t;
	}
	v = s / 1.42e8;
	h = v * 9 / 3.1415926;
	h = pow(h,1.0/3);

	printf(" 总麦粒数约为： %.3e\n",s);
	printf(" 折合体积约为： %.0f立方米\n",v);
	printf(" 正圆锥麦堆高约为： %.0f米\n",h);

	Endl();
}
/*
 * 买马钉
 */
void c012test(){
	
	double t, s;
	int n;
	printf("请输入n:");
	scanf("%d",&n);
	t = 1;
	s = 1;
	for(int i = 2; i != n; i++){
		t *= 2;
		s += t;
	}
	printf(" 总共需要花费 %.4f 卢布。", s / 400); //换算成卢布输出

	Endl();
}
/*
 * 分数不等式
 *  n < 1 + 1/2 + 1/3 +...+1/m < n + 1
 * 求解调和级数不等式
 */
void c021(){
	long c, d, i, n;
	double s;
	cout<<"求  n < 1 + 1/2 + 1/3 +...+1/m < n + 1的整数m."<<endl;
	cout<<"请输入n: ";
	cin>>n;
	i = 0;
	s = 0;
	while(s < n){ //计算下限区间
		i += 1;
		s += 1.0/i;
	}
	c = i;
	while(s < n + 1){//计算上限区间
		i += 1;
		s += 1.0/i;
	}
	d = i - 1;

	cout<<endl<<"满足不等式的m为: "<<c <<" <= m <= "<< d <<endl;

	Endl();
}

/*
 * 解不等式 d< 1+ 1/2 - 1/3 + 1/4 - 1/5+...+-1/m 的解
 */
void c022(){
	long d, m , k;
	double s;
	cout<<"请输入d:";
	cin>>d;
	cout<<endl<<" d <1+1/2-1/3+1/4-1/5...1+-1/m的解:"<<endl;
	m = 1;
	s = 1;
	while(true){
		s = s + 1.0/m + 1.0/(m+1) -1.0/(m+2);
		if(s < d)
			break;
		m += 3;
	}
	cout<<"m>="<<m<<endl; //区间解
	k = 1;
	s = 0;
	while(k < m){
		if(k%3 > 0){
			s += 1.0/k;
		}else{
			s -= 1.0/k;
		}
		if (s > d)
			cout<<"m="<<m; //一个离散解
		k++;
	}

	Endl();

}

/*
 * 求n的阶乘n！
 */
void c031(){
	int n;
	cout<<"请输入n："<<endl;
	cin>>n;
	int t = 1;
	for(int i = 1; i <= n; i++){
		t *= i;
	}
	cout<<n<<"!= "<<t<<endl;

	Endl();
}
//递归求n的阶乘n！
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
	cout<<"请输入n："<<endl;
	cin>>n;
	long y = fac(n);
	cout<<n<<"!= "<<y<<endl;
	Endl();
}

/*
 *选择计算排列数A(n,m) 与组合数C(n,m)
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

// abc = a！+b！+c！
void c034(){

	int m, n;
	cout<<"三位阶乘和数有:";
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


