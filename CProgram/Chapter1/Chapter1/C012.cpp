#include <stdio.h>

void main(){

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

	scanf("%d",&n);//结束

}