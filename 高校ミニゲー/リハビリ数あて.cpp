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
	printf("1`10‚ğ‘Å‚ÄB\n");
	while(1){
	scanf("%d",&b);
	c=c++;
	if(a<b){
	printf("”‚ª‘å‚«‚¢‚æ\n");
	}
	else if(a>b){
	printf("”‚ª¬‚³‚¢‚æ\n");
	}
	else{
		printf("“–‚½‚è‚¾‚æ\n");
		break;
	}
	if(c==5){
	printf("I‚í‚è‚¾‚æ\n");
	printf("³‰ğ‚Í%d‚¾‚æ\n",a);
	break;
		}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}