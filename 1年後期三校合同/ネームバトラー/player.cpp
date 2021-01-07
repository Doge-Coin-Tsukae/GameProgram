#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"player.h"

#define MOJIRETU (15)

void player_soto(void) {
	printf("����������������������������������������������������������������������\n");
	printf("��                                              ��   ������������   ��\n");
	printf("��                                              ��   ������������   ��\n");
	printf("��                                              �� ��������������   ��\n");
	printf("��                                              ��   ������������   ��\n");
	printf("��                                              ��   ������������   ��\n");
	printf("��                                              ��     ����������   ��\n");
	printf("��                                              �� �����Z���������� ��\n");
	printf("����������������������������������������������������������������������\n");
}

//�v���C���[�ɖ��O����͂�����
void player_name(bool hantei) {
	//�v���C���[�����肩�𔻒f���ĕ��͂�����
	if (hantei) {
		printf("�͒���");
	}
	else {
		printf("����̊͒���");
	}

	printf("���O����͂��Ă�������\n");

}

//�v���C���[�ɑD�̖��O����͂�����
void ship_name(bool hantei) {
	//�v���C���[�����肩�𔻒f���ĕ��͂�����
	if (hantei) {
		printf("�͒�");
	}
	else {
		printf("����̊͒�");
	}

	printf("����D����D�̖��O����͂��Ă�������\n");
}

//���͏���
int input(char name[32]) {
	scanf("%s", name);		//���͏���
	rewind(stdin);

	return name[32];
}

void frame(void) {
	printf("����������������������������\n");
	printf("                                      ��                        ��\n");
	printf("                                      ����������������������������\n");
}

//���O����ASCII�ŗ����̎�����߂�
int player_atai(char name[32]) {
	//�ϐ��錾
	int kazu, i;		//�����𐔂���(kazu)
	int ascii = 0;	//���O��ASCII�ɂ��Ď�ɂ���

	//���O�̐��𐔂���
	kazu = strlen(name);
	//moji�z��̓��e��ASCII�ցA�ϊ�����
	for (i = 0; i < kazu; i++) {
		ascii += name[i];
	}

	//��������
	ascii *= 3597;

	return ascii;
}

//�v���C���[�̔\�͔��f
int player_efficiency(int ascii) {
	//�ϐ��錾
	int EFFICIENCY;

	EFFICIENCY = (ascii % 500 + 1);		//���� = 1�`500

	//ASCII��0�ȉ��ɂȂ��Ă��܂����Ƃ��Ƀv���X�ɂ��鏈��
	if (EFFICIENCY <= 0) {
		EFFICIENCY -= (EFFICIENCY * 2);
	}

	return EFFICIENCY;
}

//�v���C���[�̊O�������߂�
int player_graphic(int ascii) {
	//�ϐ��錾
	int GRA;

	GRA = (ascii % 5);	//0�`10�Ŋ�̃p�^�[�������

	//ASCII��0�����ɂȂ����Ƃ��Ƀv���X�ɂ��鏈��
	if (GRA < 0) {
		GRA -= (GRA * 2);
	}

	return GRA;
}

//��̍쐬���I��������Ɍ��ʂ�\������
void plyaer_display(char name[32], int efficiency, int gra) {
	printf("%s �͒�\n", name);
	printf("�v���C���[�̔\��:%d\n", efficiency);
	printf("�O��:");
	if (gra == 0) {
		printf("�@�B������\n");
	}
	else if (gra == 1) {
		printf("�M����\n");
	}
	else if (gra == 2) {
		printf("���\n");
	}
	else if (gra == 3) {
		printf("����\n");
	}
	else if (gra == 4) {
		printf("����\n");
	}
}

//�D�̖��O����ASCII�ŗ����̎�����
int ship_atai(char name[32]) {
	//�ϐ��錾
	int kazu, j;
	int ascii = 0;

	//���O�̐��𐔂���
	kazu = strlen(name);
	//moji�z��̓��e��ASCII�ցA�ϊ�����
	for (j = 0; j < kazu; j++) {
		ascii += name[j];
	}

	//��������
	ascii *= 447;

	return ascii;
}

//�D�̗̑͂̐ݒ�
int ship_hp(int ascii) {
	//�ϐ��錾
	int hp;

	hp = (ascii % 10000 + 6000);		//HP = 6000�`16000

	//HP�̐��l��0�ȉ��ɂȂ����ꍇ
	if (hp <= 0) {
		hp -= (hp * 2);
	}

	return hp;
}

//�D�̓��A���́A��������̐ݒ�
int ship_parts(int ascii) {
	//�ϐ��錾
	int parts;

	parts = ascii % 3;			//0�`2�̒l������

	//�ϐ���0�ȉ��ɂȂ����ꍇ
	if (parts <= 0) {
		parts  -= (parts * 2);
	}

	return parts;
}

//���X��^����̐ݒ�
int ship_weapon_t(int head, int t) {
	//����0�̒l���������ꍇ
	if (head == 0) {
		t += 1;
	}
	return t;
}

//����^����̐ݒ�
int ship_weapon_xl(int head, int xl) {
	//����1�̒l���������ꍇ
	if (head == 1) {
		xl += 2;
	}
	return xl;
}

//��^����̐ݒ�
int ship_weapon_l(int head, int botom, int leg, int l) {
	//����2�̒l���������ꍇ
	if (head == 2) {
		l += 5;
	}

	//���̂�0�̒l���������ꍇ
	if (botom == 0) {
		l += 10;
	}

	//�����0�̒l���������ꍇ
	if (leg == 0) {
		l += 3;
	}

	return l;
}

//���^����̐ݒ�
int ship_weapon_m(int botom, int leg, int m) {
	//���̂�1�̒l���������ꍇ
	if (botom == 1) {
		m+= 12;
	}

	//�����0�̒l���������ꍇ
	if (leg == 1) {
		m += 4;
	}

	return m;
}

//���^����̐ݒ�
int ship_weapon_s(int botom, int leg, int s) {
	//���̂�2�̒l���������ꍇ
	if (botom == 2) {
		s += 18;
	}

	//�����0�̒l���������ꍇ
	if (leg == 2) {
		s += 8;
	}

	return s;
}

//1�ڂ̕���̖��O����
int moji1(char moji[MOJIRETU], int head) {
	if (head == 0) {
		strcpy(moji, "�^�C�^�������X");
	}
	else if (head == 1) {
		strcpy(moji, "���ە���C");
	}
	else {
		strcpy(moji, "��^���e�C");
	}

	return moji[MOJIRETU];
}

//2�ڂ̕���̖��O����
int moji2(char moji[MOJIRETU], int head, int botom) {
	if (botom == 0 && head != 2) {
		strcpy(moji, "��^���e�C");
	}
	else if (botom == 1) {
		strcpy(moji,"�}�X�h���C�o�[");
	}
	else if (botom == 2) {
		strcpy(moji,"�I�[�g�L���m��");
	}
	else {
		strcpy(moji, "");
	}

	return moji[MOJIRETU];
}

//3�ڂ̕���̖��O����
int moji3(char moji[MOJIRETU], int head, int botom, int leg) {
	if (leg == 0 && head != 2 && botom != 0) {
		strcpy(moji, "��^���e�C");
	}
	else if (leg == 1 && botom != 1) {
		strcpy(moji, "�}�X�h���C�o�[");
	}
	else if (leg == 2 && botom != 2) {
		strcpy(moji, "�I�[�g�L���m��");
	}
	else {
		strcpy(moji, "");
	}

	return moji[MOJIRETU];
}

//�D�̍쐬���I��������Ɍ��ʂ�\������
void ship_display(char name[32], int HP, int HEAD, int BOTOM, int LEG, int WEAPON_T, int WEAPON_XL, int WEAPON_L, int WEAPON_M, int WEAPON_S) {
	printf("%s��\n", name);
	printf("�D�̑ϋv��:%d\n", HP);
	printf("��:%d\n", HEAD);
	printf("����:%d\n", BOTOM);
	printf("�r��:%d\n", LEG);
	printf("����̐�:T:%d XL:%d L:%d M:%d S:%d\n", WEAPON_T, WEAPON_XL, WEAPON_L, WEAPON_M, WEAPON_S);
}