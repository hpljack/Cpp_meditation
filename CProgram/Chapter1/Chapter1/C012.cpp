#include <stdio.h>

void main(){

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

	scanf("%d",&n);//����

}