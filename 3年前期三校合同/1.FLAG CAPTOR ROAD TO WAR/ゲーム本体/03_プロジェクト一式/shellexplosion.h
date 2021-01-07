#pragma once

#include "gameobject.h"

class CShellExplosion : public CGameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	static ID3D11ShaderResourceView*	m_Texture;			//‰æ‘œƒf[ƒ^

	int m_Count;

public:
	static void LoadTexture();
	static void UnLoadTexture();
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
