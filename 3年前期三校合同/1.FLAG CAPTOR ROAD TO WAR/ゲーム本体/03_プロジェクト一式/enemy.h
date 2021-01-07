#pragma once

#include "gameobject.h"

class CEnemy : public CGameObject	//継承(インヘリタンス)
{
private:
	CAnimationModel* m_Animodel;	//3Dアニメーションモデルクラス
	//static CModel* m_Model;			//3Dモデルクラス
	D3DXVECTOR3		m_ModelRot;
	CSIGHT* m_Sight;			//照準
	CWEAPON* m_Weapon;			//所持武器

	TEAM_NUMBER		m_TeamNumber;			//味方か敵かの識別

	char*	m_OldAnimationChara;	//アニメーションの名前の旧名
	char*	m_NowAnimationChara;	//現在のアニメーションの名前
	int		m_Frame = 0;			//アニメーションのフレーム
	float	rate = 0;				//アニメーションブレンドのレート

	//ヘルパー関数
	void Update_AI();

	void ChangeAnimation(char* Name);
public:
	CEnemy() {}
	~CEnemy() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void LookPlayer();		//プレイヤーを見る
	void Death();

	void Load(FILE*fp, int line);
};