#include<stdio.h>
#include<string.h>
#include"player.h"
#include"battle.h"
#include"shori.h"
#include"character.h"
#include"serif.h"
#include"conioex.h"

//�^�C�g���\��
void title(void) {

	int i , j;
	const char *title[7] = { "      ��              ��                  ��          �� �� ��    �� ��",
							 "��������������  ��������������  ��������������������  ��������  ��������",
							 "��  ������  ��  ��    ��    ��           ����         ��=��=��     ��",
							 "      ��          ����������          ����  ����      ��������      ��  ��",
							 "��������������    ��--��--��       ����        ����      ��          ����",
							 "      ��          ��--��--��     ����            ����  ������      �� �� ��",
							 "    ����          ����������  ����                  ���� ��     ����    ��",
	};

	int sound;
	sound = opensound("music/UnicronMedley.mp3");
	playsound(sound, 1);
	//�J�[�\���폜
	setcursortype(NOCURSOR);

	for (i = 0; i <= 30; i++) {
		clrscr();

		for (j = 0; j < 8; j += 2) {
			gotoxy(i - j, 10 + j);
			printf("%s\n", title[j]);
		}

		for (j = 1; j < 6; j += 2) {
			gotoxy(60 -j -i, 10 + j);
			printf("%s\n", title[j]);
		}

		
		msleep(20);
	}

	gotoxy(54, 18);
	printf("�` s p a c e  w a r s �`");
	gotoxy(60, 20);
	printf("press enter");
	rewind(stdin);
	getchar();

	closesound(sound);

	for (i = 0; i <= 35; i++) {//�F�����
		clrscr();

		for (j = 0; j < 7; j ++) {
			gotoxy(30 - j , 10 + j +i);
			printf("%s\n", title[j]);
		}
		msleep(30);
	}
	msleep(100);
}

//�v���C���[��D�̃f�[�^����o�͂���
void player_sakusei(void) {
	//�ϐ��錾
	int i = 0;
	int seed[2];	//ASCII�𗐐��ɕϊ�����
	bool hantei = true;		//�\������Ƃ��Ƀv���C���[�Ƒ�������ʂ���
	int sound;
	sound = opensound("music/MoonBase2.mp3");

	//��ʃN���A
	clrscr();
	playsound(sound, 1);
	//�v���[���[�̖��O�����
	gotoxy(1, 35);
	player_soto();

	textcolor(14);
	input_player_voice();
	gotoxy(3 +  1, 37);
	serif_display();
	input_player_voice_2();
	gotoxy(3 +  1, 38);
	serif_display();
	textcolor(15);

	gotoxy(40, 10);
	player_name(hantei);		//��̖������:
	gotoxy(39,11);
	frame();
	gotoxy(41, 12);
	input(player[0].NAME);		//���͏���
	clrscr();

	gotoxy(1, 35);
	player_soto();

	textcolor(14);
	input_ship_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	input_ship_voice_2();
	gotoxy(3 + 1, 38);
	serif_display();
	textcolor(15);

	gotoxy(34, 10);
	ship_name(hantei);			//�D�̖������
	gotoxy(39, 11);
	frame();
	gotoxy(41, 12);
	input(ship[0].NAME);		//���͏���

	//ASCII�̗����𓾂�(��̕�)
	seed[0] = player_atai(player[0].NAME);

	//��̔\��
	player[0].EFFICIENCY = player_efficiency(seed[0]);
	//��̃O���t�B�b�N
	player[0].GRA = player_graphic(seed[0]);

	//ASCII�̗����𓾂�(�D�̕�)
	seed[0] = ship_atai(ship[0].NAME);

	//�D�̃f�[�^
	ship[0].HP = ship_hp(seed[0]);		//�D�̑ϋv�l
	seed[0] = seed[0] /= 13;			//ASCII�œ����l��13�Ŋ���(���̃p�[�c�Ɣ��̂�h������)
	ship[0].HEAD = ship_parts(seed[0]);		//�D�̐擪����
	seed[0] = seed[0] /= 17;			//ASCII�œ����l��17�Ŋ���(���̃p�[�c�Ɣ��̂�h������)
	ship[0].BOTOM = ship_parts(seed[0]);		//�D�̓��̕���
	seed[0] = seed[0] /= 19;			//ASCII�œ����l��19������(���̃p�[�c�Ɣ��̂�h������)
	ship[0].LEG = ship_parts(seed[0]);			//�D�̌������
	ship[0].WEAPON_T = ship_weapon_t(ship[0].HEAD, ship[0].WEAPON_T);		//���X��^�̕�����K��
	ship[0].WEAPON_XL = ship_weapon_xl(ship[0].HEAD, ship[0].WEAPON_XL);	//����^�̕�����K��
	ship[0].WEAPON_L = ship_weapon_l(ship[0].HEAD, ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_L);		//��^�̕�����K��
	ship[0].WEAPON_M = ship_weapon_m(ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_M);		//���^�̕�����K��
	ship[0].WEAPON_S = ship_weapon_s(ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_S);		//���^�̕�����K��
	moji1(ship[0].WEA_MOJI1, ship[0].HEAD);		//1�Ԗڂ̕���̖��O���K��
	moji2(ship[0].WEA_MOJI2, ship[0].HEAD, ship[0].BOTOM);		//2�Ԗڂ̕���̖��O���K��
	moji3(ship[0].WEA_MOJI3, ship[0].HEAD, ship[0].BOTOM, ship[0].LEG);		//3�Ԗڂ̕���̖��O���K��

	//�����f�[�^���o��
	clrscr();
	gotoxy(1, 35);
	player_soto();

	textcolor(14);
	input_result_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	textcolor(15);

	gotoxy(1, 3);
	plyaer_display(player[0].NAME, player[0].EFFICIENCY, player[0].GRA);		//��̃f�[�^��\��
	gotoxy(1, 7);
	ship_display(ship[0].NAME, ship[0].HP, ship[0].HEAD, ship[0].BOTOM, ship[0].LEG, ship[0].WEAPON_T, ship[0].WEAPON_XL, ship[0].WEAPON_L, ship[0].WEAPON_M, ship[0].WEAPON_S);	//�D�̃f�[�^���o��
	getchar();

	//����𑊎�p�ɂ���
	hantei = false;
	clrscr();

	//����̃f�[�^���쐬����
	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	input_eplayer_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	input_eplayer_voice_2();
	gotoxy(3 + 1, 38);
	serif_display();
	textcolor(15);

	gotoxy(37, 10);
	player_name(hantei);		//��̖������:
	gotoxy(39, 11);
	frame();
	gotoxy(41, 12);
	input(player[1].NAME);		//���͏���
	clrscr();

	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	input_eship_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	input_eship_voice_2();
	gotoxy(3 + 1, 38);
	serif_display();
	textcolor(15);

	gotoxy(30, 10);
	ship_name(hantei);			//�D�̖������
	gotoxy(39, 11);
	frame();
	gotoxy(41, 12);
	input(ship[1].NAME);		//���͏���
	clrscr();

	//SCII�̗����𓾂�(��̕�)
	seed[1] = player_atai(player[1].NAME);

	//��̔\��
	player[1].EFFICIENCY = player_efficiency(seed[1]);
	//��̃O���t�B�b�N
	player[1].GRA = player_graphic(seed[1]);

	//ASCII�̗����𓾂�(�D�̕�)
	seed[1] = ship_atai(ship[1].NAME);

	//�D�̃f�[�^
	ship[1].HP = ship_hp(seed[1]);		//�D�̑ϋv�l
	seed[1] = seed[1] /= 13;				//ASCII�œ����l��13�Ŋ���(���̃p�[�c�Ɣ��̂�h������)
	ship[1].HEAD = ship_parts(seed[1]);		//�D�̐擪����
	seed[1] = seed[1] /= 17;			//ASCII�œ����l��17�Ŋ���(���̃p�[�c�Ɣ��̂�h������)
	ship[1].BOTOM = ship_parts(seed[1]);	//�D�̓��̕���
	seed[1] = seed[1] /= 19;			//ASCII�œ����l��19�Ŋ���(���̃p�[�c�Ɣ��̂�h������)
	ship[1].LEG = ship_parts(seed[1]);		//�D�̌������
	ship[1].WEAPON_T = ship_weapon_t(ship[1].HEAD, ship[1].WEAPON_T);		//���X��^�̕�����K��
	ship[1].WEAPON_XL = ship_weapon_xl(ship[1].HEAD, ship[1].WEAPON_XL);	//����^�̕�����K��
	ship[1].WEAPON_L = ship_weapon_l(ship[1].HEAD, ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_L);		//��^�̕�����K��
	ship[1].WEAPON_M = ship_weapon_m(ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_M);		//���^�̕�����K��
	ship[1].WEAPON_S = ship_weapon_s(ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_S);		//���^�̕�����K��
	moji1(ship[1].WEA_MOJI1, ship[1].HEAD);			//1�Ԗڂ̕���̖��O���K��
	moji2(ship[1].WEA_MOJI2, ship[1].HEAD, ship[1].BOTOM);		//2�Ԗڂ̕���̖��O���K��
	moji3(ship[1].WEA_MOJI3, ship[1].HEAD, ship[1].BOTOM, ship[1].LEG);		//3�Ԗڂ̕���̖��O���K��

	//�����f�[�^���o��
	clrscr();

	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	input_eresult_voice();
	gotoxy(3 + 1, 37);
	serif_display();
	textcolor(15);

	gotoxy(1, 15);
	plyaer_display(player[1].NAME, player[1].EFFICIENCY, player[1].GRA);		//��̃f�[�^��\��
	gotoxy(1, 19);
	ship_display(ship[1].NAME, ship[1].HP, ship[1].HEAD, ship[1].BOTOM, ship[1].LEG, ship[1].WEAPON_T, ship[1].WEAPON_XL, ship[1].WEAPON_L, ship[1].WEAPON_M, ship[1].WEAPON_S);		//�D�̃f�[�^���o��
	getchar();
	closesound(sound);
}

//�퓬�̏���
int battle_syori(void) {
	//�ϐ��錾
	int sentaku = 0;	//�v���C���[�I���̏����l
	int attacknum = 0;
	int damage = 0;
	int hit = 0;
	int defcol = 0;
	int sound;
	bool pdef = false;
	bool pvc = false;

	sound = opensound("music/AutobotDecepticonBattle.mp3");
	playsound(sound, 1);

	//�ǂ��炩�����ʂ܂ŌJ��Ԃ�
	while (1) {
		haikei_matome();
		//�����̃^�[��
		while (1) {
			//�v���[���[�ɑI������I�΂���
			sentaku = battle_input();
			//�I����1������(�U����I��)�ꍇ
			if (sentaku == 1) {
				//�U���I����ʂɓ���
				attacknum = battle_attack(ship[0].WEAPON_T, ship[0].WEAPON_XL, ship[0].WEAPON_L, ship[0].WEAPON_M, ship[0].WEAPON_S, ship[0].WEA_MOJI1, ship[0].WEA_MOJI2, ship[0].WEA_MOJI3, ship[1].HP);
				if (attacknum != 7) {
					if (attacknum == 1) {
						hit = battlepart(ship[0].WEAPON_T);
					}
					if (attacknum == 2) {
						hit = battlepart(ship[0].WEAPON_XL);
					}
					if (attacknum == 3) {
						hit = battlepart(ship[0].WEAPON_L);
					}
					if (attacknum == 4) {
						hit = battlepart(ship[0].WEAPON_M);
					}
					if (attacknum == 5) {
						hit = battlepart(ship[0].WEAPON_S);
					}
					haikei_matome();
					damage = battle_attack_shori(pdef, hit, attacknum, player[0].EFFICIENCY);
					animation(attacknum,hit);
					battle_log(damage,attacknum,hit);
					rewind(stdin);
					getchar();

					ship[1].HP -= damage;
					//�^�[���I�����ɃN�[���_�E����1���炷
					cooldowncnt();
					defcol--;
					hit = 0;
					break;
				}
				haikei_matome();

			}

			else if (sentaku == 2) {
				if (defcol <= 0) {
					haikei_matome();
					defense_hyoji();
					gotoxy(4, 40);
					serif_display();
					rewind(stdin);
					getchar();
					pdef = true;
					defcol = 3;
					break;
				}
				else {
					haikei_matome();
					defence_error();
					gotoxy(4, 40);
					serif_display();
					printf("(%d�^�[��)", defcol);
					rewind(stdin);
					getchar();
				}
			}
			
			else if (sentaku == 3) {
				cooldowncnt();
				defcol--;
				break;
			}

			else {
			}

		}

		//���肪���񂾂珟���t���O�����ă��[�v�𔲂���
		if (ship[1].HP <= 0) {
			pvc = true;
			break;
		}

		//����̃^�[��
		haikei_matome();
		//�U���I������
		ship[0].HP = ai_battle(pdef,ship[0].HP,player[1].EFFICIENCY, ship[1].WEA_MOJI1, ship[1].WEA_MOJI2, ship[1].WEA_MOJI3, ship[1].WEAPON_L, ship[1].WEAPON_M, ship[1].WEAPON_S);
		pdef = false;
		hit = 0;

		//���������񂾂����f����
		if (ship[0].HP <= 0) {
			break;
		}
	}

	closesound(sound);

	return pvc;
}

//���s��ʂ�\������
void win_lose(bool victory) {
	int i;
	int scream;

	scream = opensound("se/scream.mp3");

	clrscr();
	player_soto();

	//�����t���O�͓��������ǂ���
	if (victory) {
		fune();
		textcolor(14);
		won();
		gotoxy(3 + 1, 37);
		serif_display();
		textcolor(15);
		getchar();
	}
	else {
		playsound(scream, 0);
		textcolor(14);
		failed();
		gotoxy(3 + 1, 37);
		serif_display();
		textcolor(15);

		for (i = 0; i < 8; i++) {
			fune_move(i);
		}
		msleep(1500);
	}

	closesound(scream);
}

//���v���C���邩�ǂ���
int end(void) {
	//�ϐ��錾
	bool refrain = true;	//�J��Ԃ����I��邩��m��ϐ�
	int key = 0;		//���݂����Ă���L�[
	int getkey = 0;		//�L�[�{�[�h���͂̏K��

	//�ǂ��炩�I�Ԃ܂Ń��[�v
	clrscr();
	gotoxy(1, 35);
	player_soto();
	textcolor(14);
	retry();
	gotoxy(3 + 1, 37);
	serif_display();
	textcolor(15);
	while (1) {

		gotoxy(40, 11);
		clreol();
		//�L�[��0�̏ꍇ
		if (key == 0) {
			printf("��A �͂� ������");
		}
		//�L�[��1�̏ꍇ
		else {
			printf("�͂� ��A ������");
		}

		//�L�[�{�[�h���͑҂�
		getkey = getch();

		//���L�[����͂����ꍇ
		if (getkey == 0x4B && key > 0) {
			key--;
		}
		//�E�L�[����͂����ꍇ
		if (getkey == 0x4D && key < 1) {
			key++;
		}
		//�G���^�[�L�[����͂����ꍇ
		if (getkey == 0x0d) {
			if (key == 0) {		//�L�[��"�͂�"��I��ł����ꍇ
				connldownreflesh();
				clrscr();
				break;
			}
			else {		//�L�[��"������"��I��ł����ꍇ
				refrain = false;
				break;
			}
		}

	}

	return refrain;
}

//�퓬��ʂ��܂Ƃ߂�
void haikei_matome(void) {
	clrscr();
	haikei(1, 1);
	haikei(1, 34);
	fune();
	enemy_fune();
	battle_display(ship[1].NAME, player[1].NAME, ship[1].HP, 4, 2, 15);		//��ʕ\��
	battle_display(ship[0].NAME, player[0].NAME, ship[0].HP, 4, 35, 14);		//��ʕ\��
	character_graf(player[0].GRA,  51,  35);
	character_graf(player[1].GRA,  51,  2);
}