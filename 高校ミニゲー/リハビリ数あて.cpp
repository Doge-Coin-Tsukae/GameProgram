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
	printf("1〜10を打て。\n");
	while(1){
	scanf("%d",&b);
	c=c++;
	if(a<b){
	printf("数が大きいよ\n");
	}
	else if(a>b){
	printf("数が小さいよ\n");
	}
	else{
		printf("当たりだよ\n");
		break;
	}
	if(c==5){
	printf("終わりだよ\n");
	printf("正解は%dだよ\n",a);
	break;
		}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}