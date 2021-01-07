#include<stdio.h>
#include<string.h>
#include"battle.h"

#define CONIOEX
#include"conioex.h"

#define MOJIRETU (15)

//�ϐ��錾
int key = 0;
int getkey;
int cooldown[3] = { 0,0,0 };
int ai_cooldown[3] = { 0,0,0 };

//�퓬��ʂ̘g
void haikei(int x,int y) {
	gotoxy(x, y);
	printf("����������������������������������������������������������������������\n");
	printf("��                                              ��                  ��\n");
	printf("��                                              ��                  ��\n");
	printf("��                                              ��                  ��\n");
	printf("��                                              ��                  ��\n");
	printf("��                                              ��                  ��\n");
	printf("��                                              ��                  ��\n");
	printf("��                                              ��                  ��\n");
	printf("����������������������������������������������������������������������\n");
}

//�L�����N�^�[�̃O���t�B�b�N
void character_graf(int grafnum,int x,int y) {
	if (grafnum == 0) {			//���{�b�g
		gotoxy(x, y);
		printf("     ________     ");
		gotoxy(x, y + 1);
		printf("||  | ______ |  ||");
		gotoxy(x, y + 2);
		printf("||  | |����| |  ||");
		gotoxy(x, y + 3);
		printf("����| |  ��| |����");
		gotoxy(x, y + 4);
		printf("����|  ----  |����");
		gotoxy(x, y + 5);
		printf("����|--------|����");
		gotoxy(x, y + 6);
		printf("������������������");
	}
	else if(grafnum == 1){			//�M����
		gotoxy(x, y);
		printf("|�_  _______  �^| ");
		gotoxy(x, y + 1);
		printf("|  �^�_ �� �^�_ | ");
		gotoxy(x, y + 2);
		printf("|�^  ���_�^�� �_| ");
		gotoxy(x, y + 3);
		printf("|       ��      | ");
		gotoxy(x, y + 4);
		printf("----------------- ");
		gotoxy(x, y + 5);
		printf("  �������Z������  ");
		gotoxy(x, y + 6);
		printf("������������������");
	}
	else if (grafnum == 2) {			//���
		gotoxy(x, y);
		printf("    |  | | |  |   ");
		gotoxy(x, y + 1);
		printf("  |  |--==--|  |  ");
		gotoxy(x, y + 2);
		printf("|  | ---  --- |  |");
		gotoxy(x, y + 3);
		printf("  |  |  == |  |   ");
		gotoxy(x, y + 4);
		printf(" || |  |  |  | || ");
		gotoxy(x, y + 5);
		printf("||��������������||");
		gotoxy(x, y + 6);
		printf("������������������");
	}
	else if (grafnum == 3) {			//����
		gotoxy(x, y);
		printf("  ______________  ");
		gotoxy(x, y + 1);
		printf("�^  ��      ��  �_");
		gotoxy(x, y + 2);
		printf("|       ��       |");
		gotoxy(x, y + 3);
		printf("|       ��       |");
		gotoxy(x, y + 4);
		printf("������������������");
		gotoxy(x, y + 5);
		printf("������������������");
		gotoxy(x, y + 6);
		printf("������������������");
	}
	else {			//����
		gotoxy(x, y);
		printf("|                |");
		gotoxy(x, y + 1);
		printf("-|-|�^^^^^^^�_|-|-");
		gotoxy(x, y + 2);
		printf("�^(��========��)�_");
		gotoxy(x, y + 3);
		printf("|   |�_ () �^|   |");
		gotoxy(x, y + 4);
		printf("������ �_�^ ������");
		gotoxy(x, y + 5);
		printf("������������������");
		gotoxy(x, y + 6);
		printf("������������������");
	}
}

//���g�̑D�̕\��
void fune(void) {
	int i;
	const char *head[6] = { "====------=*",
							 "|������",
							 "|==-*�_",
							 "|==-*�^",
							 "|������",
							 "====------=*",
	};

	const char *botom[8] = { "{==========}",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "{==========}",
	};
	const char *leg[6] = {	"=====|----------",
							"=====|����������",
							"     |����������",
							"     |����������",
							"=====|����������",
							"=====|----------",
	};
	for (i = 0; i < 6; i++) {
		gotoxy(4, 21 + i);
		printf("%s\n", leg[i]);
	}
	for (i = 0; i < 8; i++) {
		gotoxy(20, 20 + i);
		printf("%s\n", botom[i]);
	}
	
	for (i = 0; i < 6; i++) {
		gotoxy(37, 21 + i);
		printf("%s\n", head[i]);
	}
}

//�s�k���̑D�����V�[��
void fune_move(int j) {
	int i;
	const char *head[6] = { "====------=*",
							 "|������",
							 "|==-*�_",
							 "|==-*�^",
							 "|������",
							 "====------=*",
	};

	const char *botom[8] = { "{==========}",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "|����������������",
							 "{==========}",
	};
	const char *leg[6] = {  "=====|----------",
							"=====|����������",
							"     |����������",
							"     |����������",
							"=====|����������",
							"=====|----------",
	};

	gotoxy(3, 20 + j);
	clreol();
	gotoxy(3, 28 - j);
	clreol();

	for (i = 0; i < 6; i++) {
		gotoxy(4, 21 + i + j);
		printf("%s\n", leg[i]);
	}
	for (i = 0; i < 8; i++) {
		gotoxy(20, 20 + i - j);
		printf("%s\n", botom[i]);
	}

	for (i = 0; i < 6; i++) {
		gotoxy(37, 21 + i + j);
		printf("%s\n", head[i]);
	}
	msleep(250);
}

//����̑D�̕\��
void enemy_fune(void) {
	int i;
	const char *head[6] = {  "*=------====",
							 "     ������|",
							 "       *-==|",
							 "       *-==|",
							 "     ������|",
							 "*=------====",
	};

	const char *botom[8] = { "     {==========}",
							 "����������������|",
							 "����������������|",
							 "����������������|",
							 "����������������|",
							 "����������������|",
							 "����������������|",
							 "     {==========}",
	};
	const char *leg[6] = {  "----------|=====",
							"����������|=====",
							"����������|",
							"����������|",
							"����������|=====",
							"----------|=====",
	};
	for (i = 0; i < 6; i++) {
		gotoxy(70, 21 + i);
		printf("%s\n", head[i]);
	}

	for (i = 0; i < 8; i++) {
		gotoxy(82, 20 + i);
		printf("%s\n", botom[i]);
	}

	for (i = 0; i < 6; i++) {
		gotoxy(99, 21 + i);
		printf("%s\n", leg[i]);
	}
}

//�_���[�W�\��
void battle_log(int damage, int attacknum, int hit) {
	gotoxy(3, 39);
	weapon(attacknum);
	printf("  %d����������", hit);
	gotoxy(3, 40);
	printf("%d", damage);
	printf("�_���[�W��^����");
}

//�퓬��ʂ�\������
void battle_display(char ship_name[32],char player_name[32],int you_hp,int x,int y,int text) {
	textcolor(text);
	gotoxy(x, y);
	printf("%s���F�����",ship_name);
	gotoxy(x, y + 1);
	printf("�ϋv��:%d",you_hp);
	gotoxy(x, y + 2);
	printf("���:%s",player_name);
	textcolor(15);
}

//�U���̃A�j���[�V����
void animation(int attacknum, int hit) {
	int i, j;
	int boom;
	int add = 0;
	int k;
	bool tama[2] = { false, false };

	boom = opensound("se/boom.mp3");
	k = 0;

	clrscr();
	fune();
	enemy_fune();

	if (attacknum == 1) {
		textcolor(1);
		gotoxy(42, 23);
		printf("(--)");
		gotoxy(42, 24);
		printf("(--)");
		msleep(500);
		gotoxy(44, 22);
		printf("(--)");
		gotoxy(42, 23);
		printf("(----)");
		gotoxy(42, 24);
		printf("(----)");
		gotoxy(44, 25);
		printf("(--)");
		msleep(1000);
		for (i = 0; i < 74; i++) {
			gotoxy(47 + i, 23);
			printf("=");
			gotoxy(47 + i, 24);
			printf("=");
		}
		if (hit >= 1) {
			playsound(boom, 0);
			textcolor(4);
			gotoxy(86, 21);
			printf("�܁܁܁܁܁�");
			gotoxy(82, 22);
			printf("�܁܁܁܁܁܁܁܁܁�");
			gotoxy(80, 23);
			printf("[[[]][]][][][[]]][]]][][][]");
			gotoxy(80, 24);
			printf("[[][][[[]][][[]][][[[]]]][]");
			gotoxy(82, 25);
			printf("�܁܁܁܁܁܁܁܁܁�");
			gotoxy(86, 26);
			printf("�܁܁܁܁܁�");
		}
		msleep(1000);
		textcolor(15);
	}

	if (attacknum == 2) {
		gotoxy(22, 19);
		printf("(--)");
		gotoxy(26, 19);
		printf("(--)");
		msleep(2000);

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();


				if (tama[1] == true) {
					gotoxy(13 + (add - 15), 18 + (i - 1));
					printf("       ");
					gotoxy(13 + (add - 15), 19 + (i - 1));
					printf("       ");
					gotoxy(14 + (add - 15), 18 + (i - 1));
					printf("[=+@+=]");
					gotoxy(14 + (add - 15), 19 + (i - 1));
					printf("[=+@+=]");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 18 + i);
					printf("       ");
					gotoxy(17 + add, 19 + i);
					printf("       ");
					gotoxy(18 + add, 18 + i);
					printf("[=+@+=]");
					gotoxy(18 + add, 19 + i);
					printf("[=+@+=]");
				}

				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("�܁܁܁܁܁�");
					gotoxy(82, 22);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(86, 26);
					printf("�܁܁܁܁܁�");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}
				add++;

				msleep(2);
			}
			gotoxy(13 + (add - 15), 18 + (i - 1));
			printf("       ");

			gotoxy(17 + add, 18 + i);
			printf("       ");

			if (tama[0] == true) {
				tama[1] = true;
			}

		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);

	}

	if (attacknum == 3) {

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();

				if (tama[1] == true) {
					gotoxy(17 + (add - 15), 20 + (i - 1));
					printf("     ");
					gotoxy(17 + (add - 15), 21 + (i - 1));
					printf("     ");
					gotoxy(18 + (add - 15), 20 + (i - 1));
					printf("---�_");
					gotoxy(18 + (add - 15), 21 + (i - 1));
					printf("---�^");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 20 + i);
					printf("       ");
					gotoxy(17 + add, 21 + i);
					printf("       ");
					gotoxy(18 + add, 20 + i);
					printf("---�_");
					gotoxy(18 + add, 21 + i);
					printf("---�^");
				}

				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("�܁܁܁܁܁�");
					gotoxy(82, 22);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(86, 26);
					printf("�܁܁܁܁܁�");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}

				add++;

				msleep(5);
			}

			gotoxy(17 + (add - 15), 20 + (i - 1));
			printf("      ");

			if (tama[0] == true) {
				tama[1] = true;
			}
		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);
	}

	if (attacknum == 4) {

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();

				if (tama[1] == true) {
					gotoxy(17 + (add - 15), 19 + (i - 1));
					printf("      ");
					gotoxy(18 + (add - 15), 19 + (i - 1));
					printf("==����");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 18 + i);
					printf("      ");
					gotoxy(17 + add, 19 + i);
					printf("      ");
					gotoxy(18 + add, 19 + i);
					printf("==����");
				}

				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("�܁܁܁܁܁�");
					gotoxy(82, 22);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(86, 26);
					printf("�܁܁܁܁܁�");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}

				add++;

				msleep(5);
			}

			gotoxy(17 + (add - 15), 19 + (i - 1));
			printf("      ");

			if (tama[0] == true) {
				tama[1] = true;
			}
		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);
	}

	if (attacknum == 5) {

		tama[0] = true;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 20; j++) {
				fune();
				enemy_fune();

				if (tama[1] == true) {
					gotoxy(17 + (add - 15), 19 + (i - 1));
					printf("  ");
					gotoxy(18 + (add - 15), 19 + (i - 1));
					printf("��");
				}

				if (tama[0] == true) {
					gotoxy(17 + add, 18 + i);
					printf("  ");
					gotoxy(17 + add, 19 + i);
					printf("  ");
					gotoxy(18 + add, 19 + i);
					printf("��");
				}


				if (add == 65 && hit > 0 || add == 80 && hit > 0) {
					enemy_fune();
					playsound(boom, 0);
					textcolor(4);
					gotoxy(86, 21);
					printf("�܁܁܁܁܁�");
					gotoxy(82, 22);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(80, 23);
					printf("[[[]][]][][][]][][]");
					gotoxy(80, 24);
					printf("[[][][[[]][][]][][]");
					gotoxy(82, 25);
					printf("�܁܁܁܁܁܁܁�");
					gotoxy(86, 26);
					printf("�܁܁܁܁܁�");
					textcolor(15);
					msleep(500);
					tama[k] = false;
					k++;
					hit--;
				}

				add++;

				msleep(3);
			}

			gotoxy(17 + (add - 15), 19 + (i - 1));
			printf("    ");

			if (tama[0] == true) {
				tama[1] = true;
			}

		}
		clrscr();
		fune();
		enemy_fune();
		msleep(1000);
	}

	closesound(boom);

}

//�^�[���I�����̃N�[���_�E���̌v�Z
void cooldowncnt(void) {
	int i;

	for (i = 0; i <= 2; i++) {
		cooldown[i]--;
	}
}

//���g���C�����Ƃ��̏���������
void connldownreflesh(void) {
	int i;

	for (i = 0; i < 3; i++) {
		cooldown[i] = 0;
		ai_cooldown[i] = 0;
	}
}

//�g�p��������̕\��
void weapon(int weapon) {
	if (weapon == 1) {
		printf("�^�C�^�������X���g�p�����B");
	}
	else if (weapon == 2) {
		printf("���ە���C���g�p�����B");
	}
	else if (weapon == 3) {
		printf("��^���e�C���g�p�����B");
	}
	else if (weapon == 4) {
		printf("�}�X�h���C�o�[���g�p�����B");
	}
	else if (weapon == 5) {
		printf("�I�[�g�L���m�����g�p�����B");
	}
	else {
		printf("�̓�����������B");
	}
}

//���͉��
int battle_input(void) {
	gotoxy(4,39);
	printf("�������܂����H\n");
	gotoxy(4, 40);
	//key�ϐ��ɂ���ăJ�[�\���̈ʒu��ς���
	if (key==0) {
		printf("��A �U�� �V�[���h�W�J �X�L�b�v");
	}
	else if (key == 1) {
		printf("�U�� ��A�V�[���h�W�J �X�L�b�v");
	}
	else {
		printf("�U�� �V�[���h�W�J ��A�X�L�b�v");
	}

	//�L�[���͑҂�
	getkey = getch();

	//�����L�[�������ꂽ�Ƃ�
	if (getkey == 0x4B && key > 0) {
		key--;
	}

	//�����L�[�������ꂽ�Ƃ�
	if (getkey == 0x4D && key < 2) {
		key++;
	}

	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (getkey == 0x0d) {
		//�L�[�̈ʒu�ɂ���ĕς���
		if (key == 0) {
			return 1;
		}
		else if (key == 1) {
			return 2;
		}
		else if (key == 2) {
			return 3;
		}
		else {

		}
	}
	return 0;
}

//�I���ōU����I�������Ƃ�
int battle_attack(int T, int XL, int L, int M, int S, char moji1[MOJIRETU], char moji2[MOJIRETU], char moji3[MOJIRETU], int eshiphp) {
	//�ϐ��̏�����(�J�[�\���������ʒu�ɂ���)
	key = 0;
	getkey = 0;

	//�U����������܂Ń��[�v
	while (1) {
		gotoxy(4, 40);
		
		//�U���ł����i���Ȃ��ꍇ
		if ((strcmp(moji2, "�}�X�h���C�o�[") != 0 && strcmp(moji3, "�}�X�h���C�o�[") != 0 && strcmp(moji2, "�I�[�g�L���m��") != 0 && strcmp(moji3, "�I�[�g�L���m��") != 0) && (strcmp(moji1, "�^�C�^�������X") != 0 || cooldown[0] > 0) && (strcmp(moji1, "���ە���C") != 0 || cooldown[1] > 0) && (strcmp(moji1, "��^���e�C") != 0 || strcmp(moji2, "��^���e�C") != 0 || strcmp(moji3, "��^���e�C") != 0) && cooldown[2] > 0) {
			return 6;
		}

		//key�ϐ��ɂ���ăJ�[�\���̈ʒu��ς���
		if (key == 0) {
			printf("�j�A");
			printf("%s  ", moji1);
			printf("%s  ", moji2);
			printf("%s", moji3);
		}
		if (key == 1) {
			printf("%s  ", moji1);
			printf("�j�A");
			printf("%s  ", moji2);
			printf("%s", moji3);
		}
		if (key == 2) {
			printf("%s  ", moji1);
			printf("%s  ", moji2);
			printf("�j�A");
			printf("%s", moji3);
		}

		//�L�[���͑҂�
		getkey = getch();

		//�����L�[����͂��ꂽ�ꍇ
		if (getkey == 0x4B && key > 0) {
			key--;
		}
		//�E���L�[����͂��ꂽ�ꍇ
		if (getkey == 0x4D && key < 2) {
			key++;
		}
		//�G���^�[�L�[����͂��ꂽ�ꍇ
		if (getkey == 0x0d) {
			gotoxy(4, 36);

			//key�ϐ��̈ʒu�ŕϓ�
			if (key == 0) {

				//���X��^���킪�I������Ă����ꍇ
				if (strcmp(moji1, "�^�C�^�������X") == 0) {

					//�N�[���_�E�����������Ă���ꍇ�U������
					if (cooldown[0] <= 0) {
						cooldown[0] = 6;		//�N�[���_�E����ݒ�

						return 1;
					}

					else {
						printf("�܂��U���ł��܂���(����%d�^�[��)",cooldown[0]);
					}
				}
				//����^���킪�I������Ă����ꍇ
				else if (strcmp(moji1, "���ە���C") == 0) {
					//�N�[���_�E�����������Ă���ꍇ�U������
					if (cooldown[1] <= 0) {
						cooldown[1] = 4;		//�N�[���_�E����ݒ�

						return 2;
					}
					else {
						printf("�܂��U���ł��܂���(����%d�^�[��)",cooldown[1]);
					}
				}
				//��^���킪�I������Ă����ꍇ
				else {
					//�N�[���_�E�����������Ă���ꍇ�U������
					if (cooldown[2] <= 0) {
						cooldown[2] = 3;		//�N�[���_�E����ݒ�

						return 3;
					}
					else {
						printf("�܂��U���ł��܂���(����%d�^�[��)", cooldown[2]);
					}
				}
			}

			else if (key == 1) {
				//��^���킪�I������Ă����ꍇ
				if (strcmp(moji2, "��^���e�C") == 0) {
					//�N�[���_�E�����������Ă���ꍇ�U������
					if (cooldown[2] <= 0) {
						cooldown[2] = 3;		//�N�[���_�E����ݒ�

						return 3;
					}
					else {
						printf("�܂��U���ł��܂���(����%d�^�[��)", cooldown[2]);
					}
				}
				//���^���킪�I������Ă����ꍇ(�N�[���_�E���͂Ȃ�)
				else if (strcmp(moji2, "�}�X�h���C�o�[") == 0) {

					return 4;
				}
				//���^���킪�I������Ă����ꍇ(�N�[���_�E���͂Ȃ�)
				else if (strcmp(moji2, "�I�[�g�L���m��") == 0) {

					return 5;
				}
				//��^���킪���Ԃ��Ă��āA�Ȃɂ��ݒ肳��Ă��Ȃ��ꍇ
				else {
					clrscr();
					return 7;
				}
			}

			else {
				//��^���킪�����ē��Ɠ��̂ɑ�^���킪��������Ă��Ȃ��ꍇ
				if (strcmp(moji3, "��^���e�C") == 0 && strcmp(moji2, "��^���e�C") != 0 && strcmp(moji1, "��^���e�C") != 0) {
					//�N�[���_�E�����������Ă���ꍇ�U������
					if (cooldown[2] <= 0) {
						cooldown[2] = 3;		//�N�[���_�E����ݒ�

						return 3;
					}
					else {
						printf("�܂��U���ł��܂���(����%d�^�[��)", cooldown[2]);
					}
				}
				//���^���킪�����ē��̂ɒ��^���킪��������Ă��Ȃ��ꍇ(�N�[���_�E���͂Ȃ�)
				else if (strcmp(moji3, "�}�X�h���C�o�[") == 0 && strcmp(moji2, "�}�X�h���C�o�[") != 0) {

					return 4;
				}
				//���^���킪�����ē��̂ɏ��^���킪��������Ă��Ȃ��ꍇ(�N�[���_�E���͂Ȃ�)
				else if (strcmp(moji3, "�I�[�g�L���m��") == 0 && strcmp(moji2, "�I�[�g�L���m��") != 0) {

					return 5;
				}
				//��^���킪���Ԃ��Ă��āA�Ȃɂ��ݒ肳��Ă��Ȃ��ꍇ
				else{
					clrscr();
					return 7;
				}
			}

			//�L�[���͑҂�
			getch();
		}
		if (getkey == 0x1b) {
			clrscr();
			return 7;
		}
	}

}

//�_���[�W�v�Z���s��
int battle_attack_shori(bool youdef,int atari,int flag,int pe) {
	//�ϐ��錾
	int damage = 0;

	//�퓬��ʂŖ�������ƃ_���[�W�v�Z����
	if (atari >= 1 || flag == 6) {
		//���X��^����̏ꍇ
		if (flag == 1) {
			damage = 4000 + (rand() & 4001) + (rand() & pe) - ((youdef * 2) * 2000);			//�_���[�W��3000�`7000�ɂ���
		}
		//����^����̏ꍇ
		else if (flag == 2) {
			damage = (((2000 + (rand() & 2001)) + (rand() & pe)) * atari) - ((youdef * 2) * 1750);		//�_���[�W��1000�`3000 * 2�ɂ���
		}
		//��^����̏ꍇ
		else if (flag == 3) {
			damage = (((200 + (rand() & 201)) + (rand() & pe)) * atari) - ((youdef * 2) * 1250);		//�_���[�W��200�`400 * ���퐔�ɂ���
		}
		//���^����̏ꍇ
		else if (flag == 4) {
			damage = (((40 + (rand() & 41)) + (rand() & pe)) * atari) - ((youdef * 2) * 750);		//�_���[�W��40�`80 * ���퐔�ɂ���
		}
		//���^��^����̏ꍇ
		else if (flag == 5) {
			damage = (((10 + (rand() & 11)) + (rand() & pe)) * atari) - ((youdef * 2) * 250);		//�_���[�W��10�`40 * ���퐔�ɂ���
		}
		//�S�Ă̕��킪�g�p�s�̏ꍇ�A���炩�̎�i�Ń_���[�W��^����(���̑���_���[�W1�̂�)
		else {
			damage = 1;		//�_���[�W��1�ɂ���
		}

		//�U����0�ȉ��ɂȂ����ꍇ0�ɂ���
		if (damage < 0) {
			damage = 0;
		}
	}
	//�S�e�O�����ꍇ�A�_���[�W0��^����
	else {
		damage = 0;		//�_���[�W��0�ɂ���
	}

	return damage;
}

//����̍U������
int ai_battle(bool youdef, int youhp,int ee, char moji1[32], char moji2[32], char moji3[32], int L, int M, int S) {
	//�ϐ��錾
	int kakuritu, attack_kakuritu, flag, i;	//�����ōU�������߂�(kakuritu),�U����i�����߂�(flag),for���̒��ɓ����
	int damage = 0;
	int hit = 0;
	int sound;
	sound = opensound("se/boom.mp3");
	//�U�������܂Ń��[�v
	while (1) {
		//���������߂�
		kakuritu = rand() % 100;

		//0�`30�̒l���o���Ƃ�
		if (kakuritu <= 30) {
			//���X��^���킪��������Ă����Ƃ�
			if (strcmp(moji1, "�^�C�^�������X") == 0) {
				//�N�[���_�E�����������Ă���Ƃ�
				if (ai_cooldown[0] <= 0) {
					ai_cooldown[0] = 6;
					flag = 1;

					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);
					break;
				}
			}
			//����^���킪��������Ă����Ƃ�
			else if (strcmp(moji1, "���ە���C") == 0) {
				//�N�[���_�E�����������Ă���Ƃ�
				if (ai_cooldown[1] <= 0) {
					ai_cooldown[1] = 4;
					flag = 2;

					for (i = 0; i < 2; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
					break;
				}
			}
			//��^���킪��������Ă����Ƃ�
			else {
				//�N�[���_�E�����������Ă���Ƃ�
				if (ai_cooldown[2] <= 0) {
					ai_cooldown[2] = 3;
					flag = 3;

					for (i = 0; i < L; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}
					damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
					break;
				}
			}
		}

		//31�`60�̒l���o���Ƃ�
		else if (kakuritu >= 31 && kakuritu <= 60) {
			//��^���킪��������Ă����Ƃ�
			if (strcmp(moji2, "��^���e�C") == 0) {
				//�N�[���_�E�����������Ă���Ƃ�
				if (ai_cooldown[2] <= 0) {
					ai_cooldown[2] = 3;
					flag = 3;

					for (i = 0; i < L; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
					break;
				}
			}
			//���^���킪��������Ă����Ƃ�(�N�[���_�E���͕K�v�Ȃ�)
			else if (strcmp(moji2, "�}�X�h���C�o�[") == 0) {
				flag = 4;

				for (i = 0; i < M; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}
				damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
				break;
			}
			//���^���킪��������Ă����Ƃ�(�N�[���_�E���͕K�v�Ȃ�)
			else if (strcmp(moji2, "�I�[�g�L���m��") == 0) {
				flag = 5;

				for (i = 0; i < S; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}

				damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
				break;
			}
			else {

			}
		}

		//61�`90�̒l���o���Ƃ�
		else if (kakuritu >= 61 && kakuritu <= 90) {
			//��^���킪��������Ă����Ƃ�
			if (strcmp(moji3, "��^���e�C") == 0 ) {
				//�N�[���_�E�����������Ă����Ƃ�
				if (ai_cooldown[2] <= 0) {
					flag = 3;
					ai_cooldown[2] = 3;

					for (i = 0; i < L; i++) {
						attack_kakuritu = rand() % 100;
						if (attack_kakuritu <= 60) {
							hit++;
						}
					}

					damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
					break;
				}
			}
			//���^���킪��������Ă����Ƃ�(�N�[���_�E���͕K�v�Ȃ�)
			else if (strcmp(moji3, "�}�X�h���C�o�[") == 0 ) {
				flag = 4;
				for (i = 0; i < M; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}

				damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
				break;
			}
			//���^���킪��������Ă����Ƃ�(�N�[���_�E���͕K�v�Ȃ�)
			else if (strcmp(moji3, "�I�[�g�L���m��") == 0) {
				flag = 5;

				for (i = 0; i < S; i++) {
					attack_kakuritu = rand() % 100;
					if (attack_kakuritu <= 60) {
						hit++;
					}
				}

				damage = battle_attack_shori(youdef, hit, flag, ee);		//�U������
				break;
			}
			else {

			}
		}

		//�m������O�ꂽ�ꍇ������x��蒼��
		else {

		}

		//�U���o���Ȃ��Ƃ����������Ƀ��[�v���甲���o��
		if ((strcmp(moji2, "�}�X�h���C�o�[") != 0 && strcmp(moji3, "�}�X�h���C�o�[") != 0 && strcmp(moji2, "�I�[�g�L���m��") != 0 && strcmp(moji2, "�I�[�g�L���m��") != 0) && (strcmp(moji1, "�^�C�^�������X") != 0 || ai_cooldown[0] > 0) && (strcmp(moji1, "���ە���C") != 0 || ai_cooldown[1] > 0) && (strcmp(moji1, "��^���e�C") != 0 || strcmp(moji2, "��^���e�C") != 0 || strcmp(moji3, "��^���e�C") != 0) && ai_cooldown[2] > 0) {
			flag = 6;
			damage = battle_attack_shori(youdef, 1, flag, ee);		//�U������
			break;
		}

	}

	youhp -= damage;

	//�^�[���I�����ɃN�[���_�E�����Ԃ�1���炷
	for (i = 0; i <= 2; i++) {
		ai_cooldown[i] -= 1;
	}
	playsound(sound, 0);
	battle_log(damage, flag, hit);
	rewind(stdin);
	getchar();

	closesound(sound);

	return youhp;
}

//�U�����
int battlepart(int kazu) {

	//�ϐ��錾
	int i;
	int atari = 0;
	int x = 8, y = 1;
	int fps = 0;
	int number = 500;
	int sum = 0;
	int enter;
	bool hit = false;

	const char *nothing[7] = { "        ",
							   "           ",
							   "             ",
							   "              ",
							   "             ",
							   "           ",
							   "        ",
	};

	const char *cursor[7] = {"      ||",
							 "   ===||===",
							 " ===  ||  ===",
							 "------��------",
							 " ===  ||  ===",
							 "   ===||===",
							 "      ||",
	};

	const char *target[7] = {"  ��������������",
							 "��              ��",
							 "��              ��",
							 "��      ��      ��",
							 "��              ��",
							 "��              ��",
							 "  ��������������"
	};

	clrscr();

	//�G���^�[�L�[���������܂Ń��[�v
	while (1) {
		if (kbhit()) {		//�ǂ����̃L�[�������ꂽ�Ƃ�
			enter = getch();		//���̃L�[�̏���"key"�ϐ��ɂ����
			if (enter == 0x0d) {		//"key"�ɓ������̂��G���^�[�L�[�������ꍇ
				if (x > 80 && x < 100) {		//�U���͈͓��̏ꍇ
					atari++;
					hit = true;
				}
				else {		//�U���͈͊O�̏ꍇ
					hit = false;
				}

				//�e�̗����X�s�[�h���� 500�`1000
				number = 500 + rand() & 501;
				sum++;
				x = 8;
				y = 1;
				fps = 0;
				clrscr();
			}
		}
		else if (x > 130) {
			number = 500 + rand() & 501;
			x = 8;
			y = 1;
			fps = 0;
			sum++;
			hit = false;
			clrscr();
		}

		if (sum == kazu) {
			break;
		}

		//number����ɂȂ�����摜����������
		if (fps > number) {

			//�󔒕\��
			for (i = 0; i < 7; i++) {
				gotoxy(x - 8, y - 1 + i);
				printf("%s\n", nothing[i]);
			}

			//�I�\��
			for (i = 0; i < 7; i++) {
				gotoxy(86, 10 + i);
				printf("%s\n", target[i]);
			}

			//�J�[�\���\��
			for (i = 0; i < 7; i++) {
				gotoxy(x, y + i);
				printf("%s\n", cursor[i]);
			}

			gotoxy(4, 39);
			printf("%d��%d��", kazu, sum + 1);

			if (hit == true) {
				textcolor(4);
				gotoxy(89, 19);
				printf("HIT");
				textcolor(15);
				msleep(50);
			}

			fps = 0;
			x += 8;
			y++;
			hit = false;
			msleep(20);
		}
		
		fps++;
	}

	return atari;
}