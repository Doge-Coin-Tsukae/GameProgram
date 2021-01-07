#pragma once

#include "gameobject.h"

class CPlayer : public CGameObject	//継承(インヘリタンス)
{
private:
	CModel* m_Model;			//3Dモデルクラス
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器
	AABB m_Colider;

	D3DXVECTOR3		m_Velocity;		//行き先座標
	TEAM_NUMBER		m_TeamNumber;	//味方か敵かの識別
	int				m_Hp;			//体力
	float			m_speed;		//足の速さ
	bool			m_Death;		//死亡フラグ

	void Update_Controll();		//キー入力
public:
	CPlayer(){}
	~CPlayer(){}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Death();		//死亡処理
	void Damage();		//ダメージ

	void Save(FILE* fp);
	void Load(FILE* fp);
	CWEAPON* GetWeapon(){return m_Weapon;}
	bool	 isDeath() { return m_Death; }
};