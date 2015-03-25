#include "C011.h"
#include "stdafx.h"
#include <stdio.h>
#include <math.h>

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

	//scanf("%d",&n);	//结束
}