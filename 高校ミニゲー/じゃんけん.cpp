#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	int GetRandom(int min,int max);
	int a,b;
	srand((unsigned int)time(NULL));
	while(1){
	a=GetRandom(1,3);
	printf("じゃんけん\n");
	printf("1=グー 2=チョキ 3=パー\n");
	
	scanf("%d",&b);
	if(b==1){
		printf("\n");
		printf("あなたはグー\n");
		printf("\n");
		printf("\n");
	}
	else if(b==2){
		printf("\n");
		printf("あなたはチョキ\n");
		printf("\n");
		printf("\n");
	}
	else if(b==3){
		printf("\n");
		printf("あなたはパー\n");
		printf("\n");
		printf("\n");
	}
	else{
		printf("\n");
		printf("(´・ω・｀)\n");
		printf("\n");
	}
	if(a==1){
	printf("私はグー！     ＿_\n");
    printf("             /｣｣｣｣\n");
    printf("            ｜っ丿\n");
    printf("      ∧_∧ / ／\n");
    printf("     ( ･ω･)／\n");
    printf("    (つ   ﾉ\n");
    printf("    ｕ-ｕ\n");
	printf("\n");
	}
	else if(a==2){
		printf("私はチョキ！\n");
        printf("           (Ｖ)\n");
        printf("           /ｱE)\n");
        printf("    ∧_∧ / ／\n");
        printf("   ( ･ω･)／\n");
        printf("  (つ   ﾉ\n");
        printf("  ｕ-ｕ\n");
		printf("\n");
	}
	else{
		printf("私はパー！\n");
        printf("        ｢｢｢h\n");
        printf("       Ｃ  ﾉ\n");
        printf(" ∧_∧ / ／\n");
        printf("( ･ω･)／\n");
        printf("つ   ﾉ\n");
        printf("ｕ-ｕ\n");
		printf("\n");
	}
	if(a==b){
		printf("あいこだよ(´・ω・｀)\n");
	}
	else if(a==1&&b==2||a==2&&b==3||a==3&&b==1){
		printf("あなたの負けだYO(´・ω・｀)\n");
		break;
	}
	else if(a==1&&b==3||a==2&&b==1||a==3&&b==2){
		printf("あなたの勝ちだYO(´・ω・｀)\n");
		break;
	}
	else{ 
		printf("1〜3だと言っただろうが！！\n");
		break;
	}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}