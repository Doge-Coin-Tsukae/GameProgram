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
	
	printf("1～10を打て。\n");
	for(c=4;c>=0;c--){
		printf("残り%d回\n",c+1);
		scanf("%d",&b);
		if(a<b){
	printf("数が大きいよ\n");
	}
	else if(a>b){
	printf("数が小さいよ\n");
	}
	else if(a==b){
		printf("当たりだよ\n");
	break;
	}
	}
	if(c==-1){
	printf("終わりだよ\n");
	printf("正解は%dだよ\n",a);
	}
	printf("もう一回？\n");
	printf("1=もう一回   2=終わる\n");
	scanf("%d",&d);
	if(d==1){
	}
	else if(d==2){
		printf("終わり\n");
		break;
	}
	else{
		printf("おしまい\n");
		break;
	}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}