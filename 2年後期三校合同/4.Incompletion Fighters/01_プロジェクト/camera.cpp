//****************************************************
//カメラのプログラム
//****************************************************

#include "camera.h"
#include "player.h"
#include "myDirect3D.h"
#include "debugproc.h"
#include "Vector.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CAM_ONE_POS_V_X		(2000.0f)					// 1Pのカメラの視点初期位置(X座標)
#define	CAM_ONE_POS_V_Y		(2000.0f)				// 1Pのカメラの視点初期位置(Y座標)
#define	CAM_ONE_POS_V_Z		(0.0f)				// 1Pのカメラの視点初期位置(Z座標)
#define	CAM_ONE_POS_R_X		(0.0f)					// 1Pのカメラの注視点初期位置(X座標)
#define	CAM_ONE_POS_R_Y		(1000.0f)				// 1Pのカメラの注視点初期位置(Y座標)
#define	CAM_ONE_POS_R_Z		(0.0f)				// 1Pのカメラの注視点初期位置(Z座標)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(25500.0f)										// ビュー平面のFarZ値

#define CAMERANANAMESPEED	(35.36f)		//カメラが進むスピード
#define MAX_CAMERA		(1)					//プレイヤー数の上限

//*****************************************************************************
//プロトタイプ宣言
//*****************************************************************************

void centercamera(D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos);

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
	GRAVITY,
};

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
		m_Length = 200.0f;
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
			m_Angle2 += 4.0f;
		}
		//下の判定が入ったとき
		else if (type == DOWN)
		{
			m_Angle2 -= 4.0f;
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
CAMERA g_camera[MAX_CAMERA];		// カメラ情報
DRAWOBJECT g_en[MAX_CAMERA];		//円情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void Camera_Initialize(void)
{

	g_camera[0].posV = D3DXVECTOR3(CAM_ONE_POS_V_X, CAM_ONE_POS_V_Y, CAM_ONE_POS_V_Z);
	g_camera[0].posR = D3DXVECTOR3(CAM_ONE_POS_R_X, CAM_ONE_POS_R_Y, CAM_ONE_POS_R_Z);

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		g_en[i].InitCircle(i);	//円の書記処理

		//g_camera[i].shake = 10.0f;
		g_camera[i].viewangle = D3DXToRadian(45.0f);
		g_camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[i].ZoomTimer = 0.0f;
		g_camera[i].Hit = false;
		g_camera[i].fly = 0.0f;
		g_en[i].ChangeCameraRot(i);
	}

	//カメラ分割
	//1P
	g_camera[0].g_view = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void Camera_Finalize(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void Camera_Update(void)
{
		centercamera(GetPos(0),GetPos(1));
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void Camera_SetCamera(int index)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[index].mtxProjection);

	// プロジェクションマトリックスの作成(3Dから2Dにする)
	D3DXMatrixPerspectiveFovLH(&g_camera[index].mtxProjection,
		g_camera[index].viewangle,		// ビュー平面の視野角
		VIEW_ASPECT,			// ビュー平面のアスペクト比
		VIEW_NEAR_Z,			// ビュー平面のNearZ値
		VIEW_FAR_Z);			// ビュー平面のFarZ値

	D3DXMATRIX mtxProj;
	D3DXMatrixIdentity(&mtxProj);

	float aspect = D3DXToRadian(45);

	float w = 1 / tanf((aspect*1.78)*0.5);
	float h = 1 / tanf((aspect)*0.5f);
	float Q = 0;//= VIEW_FAR_Z / (VIEW_FAR_Z - VIEW_FAR_Z);

	mtxProj(0, 1) = w;
	mtxProj(1, 0) = h;
	mtxProj(2, 2) = Q;
	mtxProj(2, 3) = 1.0f;
	mtxProj(3, 2) = Q * VIEW_NEAR_Z*-1;


	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[index].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera[index].mtxView);		//単位行列を作ってくれる(行列を初期がするときに使う)

// ビューマトリックスの設定

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera[index].mtxView,
		&g_camera[index].posV,		// カメラの視点
		&g_camera[index].posR,		// カメラの注視点
		&g_camera[index].vecU);	// カメラの上方向ベクトル

//カメラの座標を変更（ビュー行列）
	pDevice->SetViewport(&g_camera[index].g_view);
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[index].mtxView);
}

/*カメラ座標の変更*/
void changecamera(int type, int index)
{
	if (g_camera[index].Hit == false) {
		switch (type) {
			//前移動
		case UP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//後ろ移動
		case DOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//右移動
		case RIGHT:
			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//左移動
		case LEFT:
			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//右前
		case RIGHTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//右後ろ
		case RIGHTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//左前
		case LEFTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

			//左後ろ
		case LEFTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*50.0f;
			break;

		case FLY:
			g_camera[index].fly = 200.0f;
			break;

			//重力に引っ張られる
		case GRAVITY:
			g_camera[index].posV.y += g_camera[index].fly;
			g_camera[index].posR.y += g_camera[index].fly;

			if (g_camera[index].posV.y <= CAM_ONE_POS_V_Y)
			{
				g_camera[index].posV.y = CAM_ONE_POS_V_Y;
				g_camera[index].fly = 0.0f;
			}
			else
			{
				g_camera[index].fly -= 10.0f;
			}
			break;

			//それ以外
		default:
			break;
		}
	}

}

//カメラの注視点を受け取る
D3DXVECTOR3 GetPosR(int index)
{
	return g_camera[index].posR;
}

//カメラの動きを止める	(true=動かない,false=動く)
void Hitcamera( bool trfl,int index)
{
	g_camera[index].Hit =trfl;
}

//視野角をもとに戻す
void LoadCameraPos(int index)
{
	g_camera[index].viewangle = D3DXToRadian(45.0f);
	g_camera[index].ZoomTimer = 0.0f;
}

//カメラを真っ直ぐにズームさせる
void ZoomCamera(int index)
{
	if (g_camera[index].ZoomTimer < 4.0f)
	{

		g_camera[index].viewangle -= D3DXToRadian(0.3f);
		g_camera[index].ZoomTimer += 0.1f;
	}
}

//指定したカメラを角度に向かせる
void ChangeCameraVer(int num,int index)
{
	g_en[index].ChangeCameraRotVertical(num);
}

//指定した座標にカメラを移動させる
void ChangeCamera(int num, int index)
{
	g_en[index].ChangeCameraRot(num);
}

void centercamera(D3DXVECTOR3 P1Pos, D3DXVECTOR3 P2Pos)
{

	g_camera[0].posR = P1Pos - (GetOnlyVector(P1Pos, P2Pos) / 2);
	g_camera[0].posV = g_camera[0].posR;
	//g_camera[0].posV = vector / 2;

	g_camera[0].posR.y = CAM_ONE_POS_R_Y;
	g_camera[0].posV.x = CAM_ONE_POS_V_X;
	g_camera[0].posV.y = CAM_ONE_POS_V_Y +200;
}

CAMERA* GetCamera()
{
	return &g_camera[0];
}