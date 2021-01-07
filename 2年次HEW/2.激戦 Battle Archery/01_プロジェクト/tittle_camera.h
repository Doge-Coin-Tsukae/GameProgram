#pragma once
#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
struct TCAMERA
{
	D3DXVECTOR3 posV;			// カメラの視点
	D3DXVECTOR3 posR;			// カメラの注視点
	D3DXVECTOR3 vecU;			// カメラの上方向
	D3DXVECTOR3 posVDest;		// カメラの視点の目的位置
	D3DXVECTOR3 posRDest;		// カメラの注視点の目的位置
	D3DXVECTOR3 rot;			// カメラの回転
	float fLengthInterval;		// カメラの視点と注視点の距離
	float fHeightV;				// カメラの視点の高さ
	float fHeightR;				// カメラの注視点の高さ
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	float fRateRotAuto;			// 自動回り込み係数
	bool bMoveAuto;				// 自動回り込みON/OFF

	//D3DXMATRIX mtxView;			// ビューマトリックス
	D3DVIEWPORT9 g_view;
	float viewangle;			//視野角

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT TCamera_Initialize(void);
void TCamera_Finalize(void);
void TCamera_Update(void);
void TCamera_SetCamera(int index);
void SetTCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv, int index);