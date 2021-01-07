//****************************************************
//カメラのプログラム
//****************************************************
#include "tittle_camera.h"
#include "field.h"
#include "camera.h"
#include "myDirect3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	CAM_ONE_POS_V_X		(0.0f)					// 1Pのカメラの視点初期位置(X座標)
#define	CAM_ONE_POS_V_Y		(200.0f)				// 1Pのカメラの視点初期位置(Y座標)
#define	CAM_ONE_POS_V_Z		(2000.0f)				// 1Pのカメラの視点初期位置(Z座標)
#define	CAM_ONE_POS_R_X		(0.0f)					// 1Pのカメラの注視点初期位置(X座標)
#define	CAM_ONE_POS_R_Y		(100.0f)				// 1Pのカメラの注視点初期位置(Y座標)
#define	CAM_ONE_POS_R_Z		(2050.0f)				// 1Pのカメラの注視点初期位置(Z座標)

#define	CAM_TWO_POS_V_X		(0.0f)					// 2Pのカメラの視点初期位置(X座標)
#define	CAM_TWO_POS_V_Y		(200.0f)				// 2Pのカメラの視点初期位置(Y座標)
#define	CAM_TWO_POS_V_Z		(-2000.0f)				// 2Pのカメラの視点初期位置(Z座標)
#define	CAM_TWO_POS_R_X		(0.0f)					// 2Pのカメラの注視点初期位置(X座標)
#define	CAM_TWO_POS_R_Y		(100.0f)				// 2Pのカメラの注視点初期位置(Y座標)
#define	CAM_TWO_POS_R_Z		(-2050.0f)				// 2Pのカメラの注視点初期位置(Z座標)

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(26000.0f)										// ビュー平面のFarZ値

#define MAX_CAMERA		(2)					//プレイヤー数の上限

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
TCAMERA g_title_camera[2];		// カメラ情報
DRAWOBJECT g_en[2];		//円情報

static float hankei = 500;
static float kakudo = 90.0f;

//=============================================================================
// カメラの初期化処理
//=============================================================================
HRESULT TCamera_Initialize(void)
{

	g_title_camera[0].posV = D3DXVECTOR3(CAM_ONE_POS_V_X, CAM_ONE_POS_V_Y, CAM_ONE_POS_V_Z);
	g_title_camera[1].posV = D3DXVECTOR3(CAM_TWO_POS_V_X, CAM_TWO_POS_V_Y, CAM_TWO_POS_V_Z);
	g_title_camera[0].posR = D3DXVECTOR3(CAM_ONE_POS_R_X, CAM_ONE_POS_R_Y, CAM_ONE_POS_R_Z);
	g_title_camera[1].posR = D3DXVECTOR3(CAM_TWO_POS_R_X, CAM_TWO_POS_R_Y, CAM_TWO_POS_R_Z);

	for (int i = 0; i < MAX_CAMERA; i++)
	{
		g_title_camera[i].viewangle = D3DXToRadian(45.0f);
		g_title_camera[i].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	}

	//カメラ分割
	//1P
	g_title_camera[0].g_view = { 0, 0, SCREEN_WIDTH / 2 , SCREEN_HEIGHT, 0.0f, 1.0f };
	//2P
	g_title_camera[1].g_view = { SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT,0.0f,1.0f };

	Field_Initialize();



	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void TCamera_Finalize(void)
{
	g_title_camera[0].g_view = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f };

	Field_Finalize();
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void TCamera_Update(void)
{
	for (int i = 0; i < MAX_CAMERA; i++)
	{

		Field_Update();

		kakudo -= 0.001f;

		g_title_camera[i].posV.x = g_title_camera[i].posR.x + hankei * cosf(kakudo);
		g_title_camera[i].posV.z = g_title_camera[i].posR.z + hankei * sinf(kakudo);


		/*ここまで*/
	}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void TCamera_SetCamera(int index)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_title_camera[index].mtxProjection);

	// プロジェクションマトリックスの作成(3Dから2Dにする)
	D3DXMatrixPerspectiveFovLH(&g_title_camera[index].mtxProjection,
		g_title_camera[index].viewangle,		// ビュー平面の視野角
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
	pDevice->SetTransform(D3DTS_PROJECTION, &g_title_camera[index].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_title_camera[index].mtxView);		//単位行列を作ってくれる(行列を初期がするときに使う)

// ビューマトリックスの設定

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_title_camera[index].mtxView,
		&g_title_camera[index].posV,		// カメラの視点
		&g_title_camera[index].posR,		// カメラの注視点
		&g_title_camera[index].vecU);	// カメラの上方向ベクトル

//カメラの座標を変更（ビュー行列）
	pDevice->SetViewport(&g_title_camera[index].g_view);
	pDevice->SetTransform(D3DTS_VIEW, &g_title_camera[index].mtxView);

	Field_Draw();
}


void SetTCamera(D3DXVECTOR3 posr, D3DXVECTOR3 posv,int index)
{
	g_title_camera[index].posR = posr;
	g_title_camera[index].posV = posv;
}
