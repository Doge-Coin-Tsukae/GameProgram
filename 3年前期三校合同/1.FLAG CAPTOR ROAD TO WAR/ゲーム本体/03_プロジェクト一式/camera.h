#pragma once

#include "gameobject.h"

class CCamera : public CGameObject
{
private:
	D3DXVECTOR3 m_Target;		//�J�����̒����_
	D3DXMATRIX viewMatrix;		//�r���[�}�g���N�X
	D3DXMATRIX projectionMatrix;	//�v���W�F�N�V�����}�g���N�X

	bool m_zoom;

	void BackFront_Player();	//�v���C���[����납�猩��
	void Target_Player();	//�����_���v���C���[�̍��W�ɂ���
	void Zoom_Player();			//�v���C���[�ɃY�[������
public:
	CCamera(){}		//�R���X�g���N�^
	~CCamera(){}	//�f�X�g���N�^

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ZoomCamera() { m_zoom = 1 - m_zoom; }

	bool GetZoom() { return m_zoom; }
	D3DXMATRIX GetViewMatrix() { return viewMatrix; }
};