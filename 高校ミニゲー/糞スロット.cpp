#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int GetRandom(int min,int max);
int main(void)
{
	int a,b,c;
	srand((unsigned int)time(NULL));
	a=GetRandom(1,3);
	b=GetRandom(1,3);
	c=GetRandom(1,3);
	
	printf("%d,%d,%d\n",a,b,c);
	if(a==b&&b==c)
	printf("Ÿ‚¿‚Å‚·B\n");
	else
	printf("•‰‚¯‚Å‚·B\n");
		return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}