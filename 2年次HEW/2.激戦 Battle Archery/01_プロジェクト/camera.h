#pragma once

#include "main.h"
#include "player.h"

#define POTATO (1.0f)	//縦のアングル変換

//*****************************************************************************
//enum
//*****************************************************************************

//移動のenum
enum MOVEMENT
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	RIGHTUP,
	RIGHTDOWN,
	LEFTUP,
	LEFTDOWN,
	FLY,
	JUMP,
	GRAVITY,
};

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

	float fly;					//空中に浮いているときに進む座標
	float viewangle;			//視野角
	float ZoomTimer;			//ズーム時間のタイマー
	bool Hit;					//プレイヤーが動けないとき
} CAMERA;

//*****************************************************************************
//円のクラス
//*****************************************************************************
class DRAWOBJECT
{
private:
	float m_Angle;		// 角度
	float m_Angle2;		// 角度
	float m_Length;		// 半径の長さ

public:
	//初期処理
	void InitCircle(int index)
	{
		m_Angle = GetRot(index).y;		//円の角度にプレイヤーの角度を入れる
		m_Angle2 = 0.0f;
		m_Length = 150.0f;
	}

	//カメラ回転(左右)
	void ChangeCameraRot(int index)
	{
		m_Angle = GetRot(index).y;		//カメラアングルとプレイヤーアングルを合わせる
	}

	//カメラ回転(上下)
	void ChangeCameraRotVertical(int type)
	{
		//上の判定が入ったとき
		if (type == UP)
		{
			m_Angle2 += POTATO;
		}
		//下の判定が入ったとき
		else if (type == DOWN)
		{
			m_Angle2 -= POTATO;
		}
		else {
		}

		//上方向の移動制限
		if (m_Angle2 >= 40)
		{
			m_Angle2 = 40;
		}

		//下方向の移動制限
		if (m_Angle2 <= -90)
		{
			m_Angle2 = -90;
		}
	}

	/*ゲッター*/
	//右左のアングル
	float GetAngle()
	{
		return m_Angle;
	}

	//上下のアングル
	float GetAngle2()
	{
		return m_Angle2;
	}

	//半径を手に入れる
	float GetLength()
	{
		return m_Length;
	}

};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void Camera_Initialize(void);
void Camera_Finalize(void);
void Camera_Update(void);

void Camera_SetCamera(int index);
void changecamera(int type, int index, float cameraspeed);
D3DXVECTOR3 GetPosR(int index);
D3DXVECTOR3 GetPosV(int index);
void Hitcamera(bool trfl,int index);
void LoadCameraPos(int index);
void ZoomCamera(int index);
void ChangeCameraVer(int num, int index);
void ChangeCamera(int num, int index);
float GetAngle2(int index);
void SetCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv);
CAMERA *GetCamera(int index);