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
	printf("***�����ꂽ�I\n");
	printf("�ǂ��炩�����I��ł��������B\n");
	printf("1=***�A�Q=***�A3=�����̔��@\n");
	scanf("%d",&f);
	if(f==3){
		h=h-1;
		printf("������������\n");
		printf("�c��$%d\n",h);
		if(h==0){
			printf("���O�͔n������\n");
			printf("���Ȃ���(���K�I��)���ɂ܂����B\n");
			break;
		}
		else{
		continue;
		}
	}
	else{
	}
	printf("������H\n");
	printf("������$%d\n$",h);
	scanf("%d",&g);
	
	if(h>=g){
	}
	else{
		printf("����Ȃ����I�I\n");
		continue;
	}
	while(2){
	c=GetRandom(1,16);
	printf("*** HP%d\n\n\n\n\n\n\n\n\n",a);
	printf("*** HP%d\n\n\n",b);
		d=GetRandom(5,10);
		
	a=a-d;
	b=b-c;
	printf("***��%d�_���[�W�B\n\n\n",d);
	printf("***��%d�_���[�W�B\n\n\n\n\n\n\n\n\n",c);
	for(i=0;i<=1999999999;i++){
	}
	if(a<=0){
		printf("***��***���E�����I\n");
		if(f==1){
			printf("�����ł��B\n");
			h=h-g;
			printf("������$%d\n",h);
		}
		else{
			printf("�����ł��B\n");
			h=h+g*2;
			printf("������$%d\n",h);
		}
		break;
	}
	else if(b<=0){
		printf("***��***���E�����I\n");
		if(f==1){
			printf("�����ł��B\n");
			h=h+g*2;
			printf("������$%d\n",h);
		}
		else{
			printf("�����ł��B\n");
			h=h-g;
			printf("������$%d\n",h);
		}
		break;
	}
	else{
	}
	}
	if(h==0){
		printf("���Ȃ���(���K�I��)���ɂ܂����B\n");
		break;
	}
	else{
	}
	printf("�������H\n");
	printf("1=������� 2�`=�����܂�\n");
	scanf("%d",&j);
	if(j==1){
	}
	else{
		printf("�I���B\n");
		break;
	}
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}