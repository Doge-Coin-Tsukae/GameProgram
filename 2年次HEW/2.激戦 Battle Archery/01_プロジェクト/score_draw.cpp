//********************************************************
//	��ʂɕ\��������̊֌W�̃v���O����
//********************************************************

#include "number.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

//�O���[�o���ϐ�
int g_score[2];

void Score_Init()
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		g_score[i] = 0;
	}
}

//�X�R�A��`��
void Score_Draw(float x, float y, int score, int fig, bool bZero,int player,int size)
{
	//�g����
	int scores;

	scores = g_score[score];

	// �J���X�g�p�̍ő吔�l�����
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++) {
		count_stop_score *= 10;
	}

	//�ő�l�̕␳����
	if (scores >= count_stop_score) {
		scores = count_stop_score - 1;
	}

	//	if( bZero ) {

	for (int i = 0; i < fig; i++) {

		int n = scores % 10;
		scores /= 10;

		Number_Draw(x + NUMBER_WIDTH * (fig - (i + 1)), y, n, player, size);
	}
}

//�|���������Ƃ��̗͕\�� (�������Ƃ��̋���,�v���C���[)
void Gauge_Draw(float power ,int player)
{
	float DrawPower;
	DrawPower = power / 100;

	Sprite_Draw(TEXTURE_INDEX_ARROWPOWERBOX_BAR, SCREEN_WIDTH / 5 + SCREEN_WIDTH / 2 * player, 800, 1, 1, 350, 30);
	Sprite_Draw(TEXTURE_INDEX_ARROWPOWER_BAR, SCREEN_WIDTH / 5 + 4 + SCREEN_WIDTH / 2 * player, 800 + 2 , 1, 1, 342 * DrawPower, 26);
}

//���Ԃ�`��
void Timelimit_Draw(float x, float y, int time, int fig, bool bZero)
{
	// �J���X�g�p�̍ő吔�l�����
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++) {
		count_stop_score *= 10;
	}

	//�ő�l�̕␳����
	if (time >= count_stop_score) {
		time = count_stop_score - 1;
	}

	//	if( bZero ) {

	for (int i = 0; i < fig; i++) {

		int n = time % 10;
		time /= 10;

		Number_Draw(x + NUMBER_WIDTH * (fig - (i + 1)), y, n,2,0);
	}
}

//�X�R�A��������(�v���C���[�ԍ�,�����链�_)
void addscore(int index, int num)
{
	g_score[index] += num;
}

//�X�R�A����ɓ����(�v���C���[�ԍ�)
int getscore(int index)
{
	return g_score[index];
}