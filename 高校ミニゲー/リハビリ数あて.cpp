#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int GetRandom(int min,int max);
int main(void)
{
	
	int a,b,c;
	srand((unsigned int)time(NULL));
	a=GetRandom(1,10);
	c=0;
	printf("1�`10��łāB\n");
	while(1){
	scanf("%d",&b);
	c=c++;
	if(a<b){
	printf("�����傫����\n");
	}
	else if(a>b){
	printf("������������\n");
	}
	else{
		printf("�����肾��\n");
		break;
	}
	if(c==5){
	printf("�I��肾��\n");
	printf("������%d����\n",a);
	break;
		}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}