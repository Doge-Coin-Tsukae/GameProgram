//=============================================================================
//
// âeèàóù [shadow.h]
//
//=============================================================================
#pragma once

#include "gameobject.h"

class CSHADOW : public  CGameObject
{
private:


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTexture(char* name);
};