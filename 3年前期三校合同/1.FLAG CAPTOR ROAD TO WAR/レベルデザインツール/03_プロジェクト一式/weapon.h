#pragma once

#include "gameobject.h"

class CWEAPON : public CGameObject	//継承(インヘリタンス)
{
private:
	static CModel* m_Model;			//3Dモデルクラス
	CGameObject* m_parent;		//親のアドレスを入れる

	int Ammo;		//弾数
	int MaxAmmo;	//最大数
	int ReloadTime;	//装填時間
	int NextShootTime;//弾込め時間

	bool isReload;	//装填中か
	bool isNextShoot;	//弾を込めてるか

	void NextShoot();	//次の弾が出るまでの処

public:
	CWEAPON() {}
	~CWEAPON() {}

	static void Load();
	static void UnLoad();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Reload();	//再装填
	void Shoot(D3DXVECTOR3 Pos, D3DXVECTOR3 SPos, TEAM_NUMBER SetTeamNumber);	//弾発射(プレイヤーの座標,照準の座標)

	int GetAmmo()	{ return Ammo; }
	int GetMaxAmmo(){ return MaxAmmo; }
	int GetReloadTime() { return ReloadTime; }
	bool GetNextShoot() { return isNextShoot; }
	void Setparent(CGameObject* object) { m_parent = object; }	//照準の親のアドレスのセット
};