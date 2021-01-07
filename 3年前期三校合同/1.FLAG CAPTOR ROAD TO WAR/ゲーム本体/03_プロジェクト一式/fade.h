#pragma once

#include "gameobject.h"

class CFADE :public CGameObject
{
private:
	static ID3D11Buffer*				m_VertexBuffer;		//バッファ
	static ID3D11ShaderResourceView*	m_Texture;			//テクスチャ

	static D3DXCOLOR m_FadeColor;	//色
	static float m_Alpha;			//アルファ値
	static float m_AddAlpha;		//一度に増える量
	static bool m_bOut;				//フェードインかフェードアウトか
	static bool m_bIsFade;			//現在フェードしているか

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void Fade_Start(bool bOut, int frame, D3DCOLOR color);		//フェードスタート
	static bool Fade_IsFade(void);										//フェード中か確認
	static void SetTexture(char* SetTexture)							//テクスチャのセット
	{
		//テクスチャ読み込み
		D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
			SetTexture,
			NULL,
			NULL,
			&m_Texture,
			NULL);
	}
};