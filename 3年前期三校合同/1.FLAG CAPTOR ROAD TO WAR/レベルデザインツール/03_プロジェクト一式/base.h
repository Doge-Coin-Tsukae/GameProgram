#pragma once

#include "gameobject.h"

enum TERRITORY
{
	NONE_ZONE,			//どちらの領地ではない
	FRIENDRY_ZONE,		//友軍の領地
	ENEMY_ZONE,			//敵の領地
};

class CBASE : public CGameObject	//継承(インヘリタンス)
{
private:
	TERRITORY	m_territory;	//誰の領地か
	CModel*		m_Flag;			//旗モデル
	CCOLIDER_CIRCLE*	m_Zone;
	D3DXVECTOR2 m_Territory_Invarter;	//領地に侵入している数	(x=友軍,y=敵軍)

	int			m_Gauge;				//拠点勢力地
	int			m_Id;					//リスポーンポイントと合わせるID
	bool		test;
	//ヘルパー関数
	void Update_Colision();		//当たり判定
public:
	CBASE() {}
	~CBASE() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Save(FILE* fp);
	void Load(FILE*fp, int line);
	TERRITORY GetTerritory() { return m_territory; }
};