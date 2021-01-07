
#include "light.h"
#include "myDirect3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_LIGHT		(5)		// ライトの数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_aLight[NUM_LIGHT];		// ライト情報

//=============================================================================
// ライトの初期化処理
//=============================================================================
void Light_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice(); 
	D3DXVECTOR3 vecDir;

	// **********************************************************************************
	// 真上から照らすライト
	// **********************************************************************************
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[0], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 環境光
	g_aLight[0].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[0].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(0, &g_aLight[0]);

	// ライトを有効に
	pDevice->LightEnable(0, TRUE);


	// **********************************************************************************
	// 右壁を照らすライト
	// **********************************************************************************
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[1], sizeof(D3DLIGHT9));

	// ライトのタイプの設定
	g_aLight[1].Type =D3DLIGHT_DIRECTIONAL;

	// 拡散光
	g_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 環境光
	g_aLight[1].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

    // ライトの方向の設定
	vecDir = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[1].Direction, &vecDir);

	// ライトをレンダリングパイプラインに設定
	pDevice->SetLight(1, &g_aLight[1]);

	// ライトを有効に
	pDevice->LightEnable(1, TRUE);


	// **********************************************************************************
	// 左側を照らすライト
	// **********************************************************************************
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[2], sizeof(D3DLIGHT9));

	// ライト2のタイプの設定
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	// ライト2の拡散光の設定
	g_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト2の鏡面反射光の設定
	g_aLight[2].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

    // ライト2の方向の設定
	vecDir = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[2].Direction, &vecDir);

	// ライト2をレンダリングパイプラインに設定
	pDevice->SetLight(2, &g_aLight[2]);

	// ライト2を有効に
	pDevice->LightEnable(2, TRUE);


	// **********************************************************************************
	// 後ろ壁を照らすライト
	// **********************************************************************************
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[3], sizeof(D3DLIGHT9));

	// ライト3のタイプの設定
	
	g_aLight[3].Type = D3DLIGHT_DIRECTIONAL;

	// ライト3の拡散光の設定
	g_aLight[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト3の鏡面反射光の設定
	g_aLight[3].Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

	// ライト3の方向の設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[3].Direction, &vecDir);

	// ライト3をレンダリングパイプラインに設定
	pDevice->SetLight(3, &g_aLight[3]);

	// ライト3を有効に
	pDevice->LightEnable(3, TRUE);


	// **********************************************************************************
	// 前壁を照らすライト
	// **********************************************************************************
	// D3DLIGHT9構造体を0でクリアする
	ZeroMemory(&g_aLight[4], sizeof(D3DLIGHT9));

	// ライト4のタイプの設定

	g_aLight[4].Type = D3DLIGHT_DIRECTIONAL;

	// ライト4の拡散光の設定
	g_aLight[4].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ライト4の鏡面反射光の設定
	g_aLight[4].Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	// ライト4の方向の設定
	vecDir = D3DXVECTOR3(0.0f, -1.0f, -1.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&g_aLight[4].Direction, &vecDir);

	// ライト4をレンダリングパイプラインに設定
	pDevice->SetLight(4, &g_aLight[4]);

	// ライト4を有効に
	pDevice->LightEnable(4, TRUE);


	// ライティングモード有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	//TRUEにすると自動的にライティング
}

//=============================================================================
// ライトの終了処理
//=============================================================================
void Light_Finalize(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void Light_Update(void)
{
}

