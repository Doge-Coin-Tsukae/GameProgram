#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include"serif.h"

//�ϐ��錾
char serif[40];

//�ϐ��ɓ��ꂽ�Z���t��\��
void serif_display(void) {
	printf("%s", serif);
}

//�v���C���[�쐬��ʂ̃Z���t
void input_player_voice(void) {
	strcpy(serif,"�͒��A�C���߂łƂ��������܂��B");
}

//�v���C���[�쐬��ʂ̃Z���t
void input_player_voice_2(void) {
	strcpy(serif, "�͒��̓o�^����̂Ŗ��O�������Ă��������B");
}

//�D�쐬��ʂ̃Z���t
void input_ship_voice(void) {
	strcpy(serif, "�������ꂽ�D�̖��������^�����܂����B");
}

//�D�쐬��ʂ̃Z���t
void input_ship_voice_2(void) {
	strcpy(serif, "��D����D�̖��O�����߂Ă��������B");
}

//����������̃Z���t
void input_result_voice(void) {
	strcpy(serif, "�M���̃f�[�^�ƑD�̃f�[�^��\�����܂��B");
}

//�G�v���C���[�쐬��ʂ̃Z���t
void input_eplayer_voice(void) {
	strcpy(serif, "���ɍ���A�G�Ƃ��ēo�ꂳ����");
}

//�G�v���C���[�쐬��ʂ̃Z���t
void input_eplayer_voice_2(void) {
	strcpy(serif, "�͒��̖��O�������Ă��������B");
}

//�G�D�쐬��ʂ̃Z���t
void input_eship_voice(void) {
	strcpy(serif,"�G�Ƃ��ēo�ꂳ����");
}

//�G�D�쐬��ʂ̃Z���t
void input_eship_voice_2(void) {
	strcpy(serif, "�D�̖��O����͂��Ă��������B");
}

//�G������̃Z���t
void input_eresult_voice(void) {
	strcpy(serif, "�G�̊͒��̃f�[�^�ƑD�̃f�[�^��\�����܂��B");
}

//�h�䂪�ł��Ȃ��Ƃ��̃Z���t
void defence_error(void) {
	strcpy(serif, "�܂��g���܂���B");
}

//�h�䂷��Ƃ��̃Z���t
void defense_hyoji(void) {
	strcpy(serif, "�h��V�X�e����W�J���܂��B");
}

//���������Ƃ��̃Z���t
void won(void) {
	strcpy(serif, "�����ł�");
}

//�s�k�����Ƃ��̃Z���t
void failed(void) {
	strcpy(serif, "�����ł�");
}

//�Đ�I���̃Z���t
void retry(void) {
	strcpy(serif, "�Đ킵�܂����H");
}