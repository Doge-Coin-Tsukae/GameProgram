#pragma once
#include "gameobject.h"

class VICORDEF :public CGameObject
{
private:
	CPolygon *Serif;		//表示させる言葉のpng

	int DeleteTime;			//オブジェクトが削除されるまでの時間
	bool Delete;			//時間がたったら
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Set(bool Sets);
	bool GetDelete(){	return Delete;}
};