#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int GetRandom(int min,int max);
int main(void)
{
	
	int a,b,c,d;
	srand((unsigned int)time(NULL));
	while(1){
	a=GetRandom(1,10);
	c=0;
	
	printf("1�`10��łāB\n");
	for(c=4;c>=0;c--){
		printf("�c��%d��\n",c+1);
		scanf("%d",&b);
		if(a<b){
	printf("�����傫����\n");
	}
	else if(a>b){
	printf("������������\n");
	}
	else if(a==b){
		printf("�����肾��\n");
	break;
	}
	}
	if(c==-1){
	printf("�I��肾��\n");
	printf("������%d����\n",a);
	}
	printf("�������H\n");
	printf("1=�������   2=�I���\n");
	scanf("%d",&d);
	if(d==1){
	}
	else if(d==2){
		printf("�I���\n");
		break;
	}
	else{
		printf("�����܂�\n");
		break;
	}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}