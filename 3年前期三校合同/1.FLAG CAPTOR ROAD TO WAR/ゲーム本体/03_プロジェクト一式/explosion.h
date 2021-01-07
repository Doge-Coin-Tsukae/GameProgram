#pragma once

#include "gameobject.h"

class CExplosion : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	int m_Count;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};