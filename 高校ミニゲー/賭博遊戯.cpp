#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int GetRandom(int min,int max);
int main(void)
{
	int a,b,c,d,e,f,g,h,i,j;
	srand((unsigned int)time(NULL));
		h=10;
	while(1){
	a=100;
	b=100;
	printf("***が現れた！\n");
	printf("どちらか勝つか選んでください。\n");
	printf("1=***、２=***、3=自動販売機\n");
	scanf("%d",&f);
	if(f==3){
		h=h-1;
		printf("美味しかった\n");
		printf("残り$%d\n",h);
		if(h==0){
			printf("お前は馬鹿だな\n");
			printf("あなたは(金銭的に)死にました。\n");
			break;
		}
		else{
		continue;
		}
	}
	else{
	}
	printf("いくら？\n");
	printf("所持金$%d\n$",h);
	scanf("%d",&g);
	
	if(h>=g){
	}
	else{
		printf("足らないヨ！！\n");
		continue;
	}
	while(2){
	c=GetRandom(1,16);
	printf("*** HP%d\n\n\n\n\n\n\n\n\n",a);
	printf("*** HP%d\n\n\n",b);
		d=GetRandom(5,10);
		
	a=a-d;
	b=b-c;
	printf("***に%dダメージ。\n\n\n",d);
	printf("***に%dダメージ。\n\n\n\n\n\n\n\n\n",c);
	for(i=0;i<=1999999999;i++){
	}
	if(a<=0){
		printf("***が***が殺した！\n");
		if(f==1){
			printf("負けです。\n");
			h=h-g;
			printf("所持金$%d\n",h);
		}
		else{
			printf("勝ちです。\n");
			h=h+g*2;
			printf("所持金$%d\n",h);
		}
		break;
	}
	else if(b<=0){
		printf("***が***を殺した！\n");
		if(f==1){
			printf("勝ちです。\n");
			h=h+g*2;
			printf("所持金$%d\n",h);
		}
		else{
			printf("負けです。\n");
			h=h-g;
			printf("所持金$%d\n",h);
		}
		break;
	}
	else{
	}
	}
	if(h==0){
		printf("あなたは(金銭的に)死にました。\n");
		break;
	}
	else{
	}
	printf("もう一回？\n");
	printf("1=もう一回 2～=おしまい\n");
	scanf("%d",&j);
	if(j==1){
	}
	else{
		printf("終了。\n");
		break;
	}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}