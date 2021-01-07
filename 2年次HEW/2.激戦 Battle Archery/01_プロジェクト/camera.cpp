//****************************************************
//カメラのプログラム
//****************************************************

#include "camera.h"
#include "myDirect3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAM_ONE_POS_V D3DXVECTOR3(0.0f,180.0f,2150.0f)		// 1Pのカメラの視点初期位置
#define CAM_ONE_POS_R D3DXVECTOR3(0.0f,180.0f,45.0f)		// 1Pのカメラの注視点初期位置

#define	CAM_TWO_POS_V D3DXVECTOR3(0.0f,180.0f,-2150.0f)
#define	CAM_TWO_POS_R D3DXVECTOR3(0.0f,180.0f,-45.0f)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(100.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(8000.0f)										// ビュー平面のFarZ値

#define CAMERANANAMESPEED	(35.36f)		//カメラが進むスピード
#define MAX_CAMERA		(2)					//プレイヤー数の上限

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
CAMERA g_camera[2];		// カメラ情報
DRAWOBJECT static g_en[2];		//円情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void Camera_Initialize(void)
{

	g_camera[0].posV = CAM_ONE_POS_V;
	g_camera[1].posV = CAM_TWO_POS_V;
	g_camera[0].posR = CAM_ONE_POS_R;
	g_camera[1].posR = CAM_TWO_POS_R;

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		g_en[i].InitCircle(i);	//円の初期処理

		g_camera[i].viewangle = D3DXToRadian(45.0f);
		g_camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		g_camera[i].ZoomTimer = 0.0f;
		g_camera[i].Hit = false;
		g_camera[i].fly = 0.0f;
	}

	//カメラ分割
	//1P
	g_camera[0].g_view = { 0, 0, SCREEN_WIDTH / 2 , SCREEN_HEIGHT, 0.0f, 1.0f };
	//2P
	g_camera[1].g_view = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT,0.0f,1.0f };
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void Camera_Finalize(void)
{
	g_camera[0].g_view = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void Camera_Update(void)
{
	for (int i=0; i < MAX_CAMERA; i++)
	{
		/*横の円を割り出す*/
		float radius = g_en[i].GetAngle() * 3.14f / 180.0f;

		// 三角関数を使用し、円の位置を割り出す。
		float add_x = cos(radius) * g_en[i].GetLength();
		float add_z = sin(radius) * g_en[i].GetLength();

		// 結果ででた位置を中心位置に加算し、それを描画位置とする
	
		g_camera[i].posV.x = GetPos(i).x - add_x;
		g_camera[i].posV.z = GetPos(i).z - add_z;
		/*ここまで*/

		/*縦の円を割り出す*/
		float radius2 = g_en[i].GetAngle2() * 3.14f / 180.0f;

		// 三角関数を使用し、円の位置を割り出す。
		float add_y = sin(radius2) * g_en[i].GetLength();
		g_camera[i].posV.y = GetPos(i).y + 170.0f - add_y;

		g_camera[i].posR = GetPos(i);
		g_camera[i].posR.y = GetPos(i).y + 180.0f;

		/*ここまで*/

	}
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

	//DebugProc_Print((char*)"アングル [%f]\n", g_en[index].GetAngle());
	//DebugProc_Print((char*)"アングル2 [%f]\n", g_en[index].GetAngle2());
}

/*カメラ座標の変更*/
void changecamera(int type, int index,float cameraspeed)
{
	if (g_camera[index].Hit == false) {
		switch (type) {
			//前移動
		case UP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//後ろ移動
		case DOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//右移動
		case RIGHT:
			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//左移動
		case LEFT:
			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//右前
		case RIGHTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//右後ろ
		case RIGHTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//左前
		case LEFTUP:
			g_camera[index].posV.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//左後ろ
		case LEFTDOWN:
			g_camera[index].posV.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			g_camera[index].posV.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posV.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			g_camera[index].posR.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
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

//カメラの注視点を受け取る
D3DXVECTOR3 GetPosV(int index)
{
	return g_camera[index].posV;
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

float GetAngle2(int index)
{
	return g_en[index].GetAngle2();
}

void SetCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv)
{
	g_camera[0].posR = posr;
	g_camera[0].posV = posv;
}

//=============================================================================
// カメラの取得
//=============================================================================
CAMERA *GetCamera(int index)
{
	return &g_camera[index];
}
