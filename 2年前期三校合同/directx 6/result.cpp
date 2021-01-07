#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "sound.h"
#include "texture.h"
#include "fade.h"

//�O���[�o���ϐ��錾
static bool won;

//���U���g��ʂ̏�������
void Result_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

//���U���g��ʂ̏I������
void Result_Finalize(void)
{
}

//���U���g��ʂ̍X�V����
void Result_Update(void)
{
	//�X�y�[�X�L�[���������Ƃ��Ƀ^�C�g����ʂɖ߂� & �N���b�N����炷
	if( Keyboard_IsTrigger(DIK_SPACE) ) {
		PlaySound(SOUND_LABEL_SE_CLICK);
		Scene_Change(SCENE_INDEX_TITLE);
	}
}

//���U���g��ʂ̕`�揈��
void Result_Draw(void)
{
	//���̃Q�[���ɏ������Ă����Ƃ��������Ƃ��̉摜��ǂ�
	if (won == true) {
		Sprite_Draw(TEXTURE_INDEX_WIN, 0.0f, 0.0f);
	}
	//�s�k�����Ƃ��̉摜��ǂ�
	else
	{
		Sprite_Draw(TEXTURE_INDEX_RESULT, 0.0f, 0.0f);
	}
}

//�����t���O�����Ă�
void Wewon()
{
	won = true;
}

//�����t���O������(����������)
void Welose()
{
	won = false;
}