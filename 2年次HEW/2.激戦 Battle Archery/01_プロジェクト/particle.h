//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(int i);
void ParticleSetNum(int Num, D3DXVECTOR3 Pos,D3DXCOLOR Col, float FSizeX, float FSizeY, int NLife, int index);

