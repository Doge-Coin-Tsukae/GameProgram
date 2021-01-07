#pragma once

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DVIEWPORT9 g_view;

	float fly;
	float viewangle;			//視野角
	float ZoomTimer;			//ズーム時間のタイマー
	bool Hit;					//プレイヤーが動けないとき
} CAMERA;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Camera_Initialize(void);
void Camera_Finalize(void);
void Camera_Update(void);

void Camera_SetCamera(int index);
void changecamera(int type, int index);
D3DXVECTOR3 GetPosR(int index);
void Hitcamera(bool trfl,int index);
void LoadCameraPos(int index);
void ZoomCamera(int index);
void ChangeCameraVer(int num, int index);
void ChangeCamera(int num, int index);
CAMERA* GetCamera();