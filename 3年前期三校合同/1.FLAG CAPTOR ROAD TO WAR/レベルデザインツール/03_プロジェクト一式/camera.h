#pragma once

#include "gameobject.h"

class CCamera : public CGameObject
{
private:
	D3DXVECTOR3 m_Target;		//�J�����̒����_
	D3DXVECTOR3 m_Velocity;
	D3DXMATRIX viewMatrix;		//�r���[�}�g���N�X
	D3DXMATRIX projectionMatrix;	//�v���W�F�N�V�����}�g���N�X

	float			m_speed;	//���̑���
public:
	CCamera(){}		//�R���X�g���N�^
	~CCamera(){}	//�f�X�g���N�^

	void Init();
	void Uninit();
	void Update();
	void Controll_Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return viewMatrix; }
	D3DXMATRIX GetProjectionMatrix() { return projectionMatrix; }
};