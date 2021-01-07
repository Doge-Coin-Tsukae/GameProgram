
#pragma once

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER		(2)					//�v���C���[���̏��
#define MAX_HP			(5000)

//�A�j���[�V�����̃��[�V�����p�^�[��
enum AnimePatan
{
	ANI_DEATH,
	ANI_HIT,
	ANI_GURDED,
	ANI_STORNGKICK,
	ANI_KICK,
	ANI_STRONGPUNCH,
	ANI_PUNCH,
	ANI_MOVE,
	ANI_WAIT,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Player_Initialize(void);
void Player_Finalize(void);
void Player_Update(void);
void Player_Draw(void);
D3DXVECTOR3 GetRot(int index);
D3DXVECTOR3 GetPos(int index);
int GetHp(int index);