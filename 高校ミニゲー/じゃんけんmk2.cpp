#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
	int GetRandom(int min,int max);
	int a,b,c;
	srand((unsigned int)time(NULL));
	while(1){
	a=GetRandom(1,3);
	printf("����񂯂�\n");
	printf("1=�O�[ 2=�`���L 3=�p�[ 4=�I���\n");
	
	scanf("%d",&b);
	if(b==1){
		printf("\n");
		printf("���Ȃ��̓O�[\n");
		printf("\n");
		printf("\n");
	}
	else if(b==2){
		printf("\n");
		printf("���Ȃ��̓`���L\n");
		printf("\n");
		printf("\n");
	}
	else if(b==3){
		printf("\n");
		printf("���Ȃ��̓p�[\n");
		printf("\n");
		printf("\n");
	}
	else if(b==4){
		printf("\n");
		printf("�I��� (�L�E�ցE�M)\n");
		printf("\n");
		break;
	}
	else{
		printf("\n");
		printf("(�L�E�ցE�M)\n");
		printf("\n");
	}
	if(a==1){
	printf("���̓O�[�I   �Q_\n");
    printf("           /����\n");
    printf("          �b����\n");
    printf("    ��_�� / �^\n");
    printf("   ( ��֥)�^\n");
    printf("  (��   �\n");
    printf("  ��-��\n");
	printf("\n");
	}
	else if(a==2){
		printf("���̓`���L�I\n");
        printf("           (�u)\n");
        printf("           /�E)\n");
        printf("    ��_�� / �^\n");
        printf("   ( ��֥)�^\n");
        printf("  (��   �\n");
        printf("  ��-��\n");
		printf("\n");
	}
	else{
		printf("���̓p�[�I\n");
        printf("           ���h\n");
        printf("          �b  �\n");
        printf("    ��_�� / �^\n");
        printf("   ( ��֥)�^\n");
        printf("  ��   �\n");
        printf("  ��-��\n");
		printf("\n");
	}
	if(a==b){
		printf("����������(�L�E�ցE�M)\n");
	}
	else if(a==1&&b==2||a==2&&b==3||a==3&&b==1){
		printf("���Ȃ��̕�����YO(�L�E�ցE�M)\n");
			printf("\n");
	printf("\n");
	printf("�������H\n");
	printf("1=������� 2=�I���\n");
	scanf("%d",&c);
	if(c==1){
	}
	else if(c==2){
		printf("�I��� (�L�E�ցE�M)\n");
		break;
	}
	else{
		printf("�����I���B\n");
		break;
	}
	}
	else if(a==1&&b==3||a==2&&b==1||a==3&&b==2){
		printf("���Ȃ��̏�����YO(�L�E�ցE�M)\n");
			printf("\n");
	printf("\n");
	printf("�������H\n");
	printf("1=������� 2=�I���\n");
	scanf("%d",&c);
	if(c==1){
	}
	else if(c==2){
		printf("�I��� (�L�E�ցE�M)\n");
		break;
	}
	else{
		printf("�����I���B\n");
		break;
	}
	}
	else{ 
		printf("1�`4���ƌ��������낤���I�I\n");
			printf("\n");
	printf("\n");
	printf("�������H\n");
	printf("1=������� 2=�I���\n");
	scanf("%d",&c);
	if(c==1){
	}
	else if(c==2){
		printf("�I��� (�L�E�ցE�M)\n");
		break;
	}
	else{
		printf("�����I���B\n");
		break;
	}
	}
	
	}
	return 0;
}
int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}