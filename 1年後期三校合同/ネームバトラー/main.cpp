#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"shori.h"
#include"main.h"

//���C���֐�
int main(void) {
		title();		//�^�C�g���̕\��
		srand((unsigned int)time(0));		//�����̎�����߂�

		//�Q�[�������[�v������
	while (game) {
		player_sakusei();		//�v���C���[���쐬������
		victory = battle_syori();		//�퓬����
		win_lose(victory);		//���������\��
		game = end();		//���v���C�I��
	}
	return 0;
}

