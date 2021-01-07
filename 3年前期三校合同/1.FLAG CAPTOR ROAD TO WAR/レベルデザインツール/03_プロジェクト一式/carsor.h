#pragma once

#include "gameobject.h"

class CCARSOR :public CGameObject
{
private:
	CModel* m_Model;			//3Dモデルクラス
	D3DXVECTOR3 ppos;			//カーソルのワールド座標を入れる
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXVECTOR3* CalcScreenToWorld(
		D3DXVECTOR3* pout,
		int Sx,  // スクリーンX座標
		int Sy,  // スクリーンY座標
		float fZ,  // 射影空間でのZ値（0～1）
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