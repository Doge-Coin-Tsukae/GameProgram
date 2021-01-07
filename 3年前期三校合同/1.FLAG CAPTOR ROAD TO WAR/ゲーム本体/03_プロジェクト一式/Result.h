#pragma once

#include "scene.h"

class CResult : public CScene
{
private:
	bool m_VD;
public:
	void Init();
	void Update();

	void SetVD(bool Set) { m_VD = Set; }
};