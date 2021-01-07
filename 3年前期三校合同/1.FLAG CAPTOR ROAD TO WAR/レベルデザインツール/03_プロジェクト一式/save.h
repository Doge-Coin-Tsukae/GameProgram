#pragma once

#include"gameobject.h"

class CSAVE : public CGameObject
{
private:
	std::string filename;

public:
	void Uninit();
	void Update();
	void Data_Save();
	TCHAR* PassAsset(TCHAR path[300]);
};