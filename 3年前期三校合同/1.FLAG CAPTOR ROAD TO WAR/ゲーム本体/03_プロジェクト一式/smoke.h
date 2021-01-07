#pragma once

#include "gameobject.h"

class CSMOKE : public CGameObject
{
private:
	ID3D11Buffer*						m_VertexBuffer = nullptr;
	static ID3D11ShaderResourceView*	m_Texture;

	float m_Count;

public:
	static void Load();		//画像のロード
	static void Unload();	//画像のアンロード

	void Init();
	void Uninit();
	void Update();
	void Draw();
};