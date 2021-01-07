//****************************************************
//照準を出すプログラム
//****************************************************

#include "point.h"
#include "camera.h"
#include "texture.h"
#include "sprite.h"
#include "xfile.h"

DRAWOBJECT static g_en[MAX_PLAYER];		//円情報

//弾のクラス
class POINTER {
private:
	D3DXVECTOR3		PosPoint;				//弾のポジション
	D3DXVECTOR3		RotPoint;				// 弾の向き(回転)
	D3DXVECTOR3		SclPoint;				//弾の大きさ


public:
	//弾の初期処理
	void PointInit(int index)
	{
		g_en[index].InitCircle(index);	//円の書記処理
		PosPoint = GetPos(index);
		RotPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SclPoint = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	}

	//弾の座標を更新する
	void Update(int index)
	{
		float radius = g_en[index].GetAngle() * 3.14f / 180.0f;

		// 三角関数を使用し、円の位置を割り出す。
		float add_x = cos(radius) * g_en[index].GetLength();
		float add_z = sin(radius) * g_en[index].GetLength();

		// 結果ででた位置を中心位置に加算し、それを描画位置とする
		PosPoint.x = GetPos(index).x + add_x;
		PosPoint.z = GetPos(index).z + add_z;
		/*ここまで*/

		/*縦の円を割り出す*/
		float radius2 = g_en[index].GetAngle2() * 3.14f / 180.0f;

		// 三角関数を使用し、円の位置を割り出す。
		float add_y = sin(radius2) * g_en[index].GetLength();
		PosPoint.y = (GetPos(index).y +150.0f) + add_y;
	}

	void changepoint(int type, int index,float cameraspeed)
	{
		switch (type) {
			//前移動
		case UP:
			PosPoint.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//後ろ移動
		case DOWN:
			PosPoint.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//右移動
		case RIGHT:
			PosPoint.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//左移動
		case LEFT:
			PosPoint.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//右前
		case RIGHTUP:
			PosPoint.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//右後ろ
		case RIGHTDOWN:
			PosPoint.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//左前
		case LEFTUP:
			PosPoint.z += sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

			//左後ろ
		case LEFTDOWN:
			PosPoint.z -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;

			PosPoint.z += cos(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			PosPoint.x -= sin(g_en[index].GetAngle()*D3DX_PI / 180)*cameraspeed;
			break;

		case FLY:
			break;

			//重力に引っ張られる
		case GRAVITY:

			//それ以外
		default:
			break;
		}
	}

	//座標の確認
	D3DXVECTOR3 CheckPos()
	{
		return PosPoint;
	}

	//大きさの確認
	D3DXVECTOR3 CheckScl()
	{
		return SclPoint;
	}

	//回転の確認
	D3DXVECTOR3 CheckRot()
	{
		return RotPoint;
	}

};

POINTER  point[MAX_PLAYER];

//*****************************************************************************
//関数
//*****************************************************************************

/*初期処理*/
HRESULT Point_Initialize(void)
{
	for (int i = 0 ; i < MAX_PLAYER; i++)
	{
		point[i].PointInit(i);
	}

	SetTexture(TEXTURE_INDEX_SIGHT);

	return S_OK;
}

/*終了処理*/
void Point_Finalize(void)
{
	ReleaseTexture(TEXTURE_INDEX_SIGHT);
}

/*更新処理*/
void Point_Update(void)
{
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		point[i].Update(i);		//弾の更新処理
	}
}

/*描画処理*/
void Point_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_SIGHT,
		SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4 - 60, SCREEN_HEIGHT / 2);

	Sprite_Draw(TEXTURE_INDEX_SIGHT,
		SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4 - 60, SCREEN_HEIGHT / 2);
}

D3DXVECTOR3 Get_Pos(int index)
{
	return point[index].CheckPos();
}

void ChangePointVer(int num, int index)
{
	g_en[index].ChangeCameraRotVertical(num);
}

void ChangePoint(int num, int index,float cameraspeed)
{
	point[index].changepoint(num,index,cameraspeed);
}

void ChangePointAngle(int num,int index)
{
	g_en[index].ChangeCameraRot(num);
}