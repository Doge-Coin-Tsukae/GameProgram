#pragma once

#include "gameobject.h"

class CCARSOR :public CGameObject
{
private:
	CModel* m_Model;			//3D���f���N���X
	D3DXVECTOR3 ppos;			//�J�[�\���̃��[���h���W������
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3* CalcScreenToWorld(
		D3DXVECTOR3* pout,
		int Sx,  // �X�N���[��X���W
		int Sy,  // �X�N���[��Y���W
		float fZ,  // �ˉe��Ԃł�Z�l�i0�`1�j
		int Screen_w,
		int Screen_h,
		D3DXMATRIX* View,
		D3DXMATRIX* Prj
	);

	D3DXVECTOR3 WorldCarsor() { return ppos; }

	bool Collision(CGameObject* gameobject)
	{
		D3DXVECTOR3 direction = m_Position - gameobject->GetPosition();
		float length = D3DXVec3Length(&direction);

		if (length < m_Scale.x)
		{
			return true;
		}


		return false;
	}
};