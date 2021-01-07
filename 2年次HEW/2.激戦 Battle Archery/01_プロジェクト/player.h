
#pragma once

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER		(2)					//�v���C���[���̏��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT Player_Initialize(void);
void Player_Finalize(void);
void Player_Update(void);
void Player_Draw(void);
D3DXVECTOR3 GetRot(int index);
D3DXVECTOR3 GetPos(int index);
bool CheckHitPlayerToPlayer(D3DXVECTOR3 Ppos, D3DXVECTOR3 Bullet, D3DXVECTOR3 BulScl, int bulnum, int pnum);
void PlayerScreenDraw(void);