#pragma once

#include "gameobject.h"

class CBullet : public CGameObject
{
private:
	static CModel* m_Model;		//3Dモデルクラス
	CCOLIDER_CIRCLE*	m_Zone;		//当たり判定

	D3DXVECTOR3 m_Dir;
	float DeleteTime;		//オブジェクト消失時間
	TEAM_NUMBER m_TeamNumber;	//撃った人が敵か味方か識別

	void Update_Varios();			//変数更新
	void Update_Collision();		//当たり判定更新
public:
	CBullet() {}
	~CBullet() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSight, TEAM_NUMBER SetNUMBER);
};
