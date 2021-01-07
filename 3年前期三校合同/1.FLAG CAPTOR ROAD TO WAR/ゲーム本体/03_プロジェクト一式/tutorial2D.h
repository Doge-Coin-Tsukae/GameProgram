#pragma once

#include "gameobject.h"

class CTUTORIAL2D :public CGameObject
{
private:
	CPolygon *Gamename;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChangeTexture(char* SetTextureName);		//チュートリアルのテクスチャチェンジ
};