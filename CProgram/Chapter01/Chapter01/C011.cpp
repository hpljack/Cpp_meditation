#include "C011.h"
#include "stdafx.h"
#include <stdio.h>
#include <math.h>

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

	//scanf("%d",&n);	//����
}