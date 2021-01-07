#pragma once

#include "gameobject.h"

class CEnemyRespornPoint : public CGameObject	//継承(インヘリタンス)
{
private:
	static CModel* m_Model;			//3Dモデルクラス
	CBASE*		   m_ParrentBase;	//親の拠点(リスポーン後に向かう領地)

	int			m_Id;					//リスポーンポイントと合わせるID
	//ヘルパー関数

public:
	CEnemyRespornPoint() {}
	~CEnemyRespornPoint() {}

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};