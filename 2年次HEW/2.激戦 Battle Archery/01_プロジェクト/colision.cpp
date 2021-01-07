//****************************************************
//当たり判定のプログラム
//****************************************************

#include "colision.h"
#include "myDirect3D.h"

//*****************************************************************************
//プログラム
//*****************************************************************************

//円と点の当たり判定(円の座標,点の座標,半径)
bool CircleAndPoint(D3DXVECTOR3 pos, D3DXVECTOR3 epos,float radius)
{
	//ベクトル
	D3DXVECTOR3 xyz;
	//単位ベクトル
	float vector;

	//円の中心 - 点
	xyz = pos - epos;
	vector = sqrt((xyz.x * xyz.x) + (xyz.y * xyz.y) + (xyz.z * xyz.z));

	if (sqrt(vector*vector)<=radius)
	{
		return true;
	}

	return false;
}

//点と四角の当たり判定
bool PointtoSquare(D3DXVECTOR3 Point,D3DXVECTOR3 Square,D3DXVECTOR3 SquareScl,int rupe,bool Used)
{
	for (int i = 0; i < rupe; i++)
	{
		if (Point.x >= Square.x - (100.0f * SquareScl.x) && Point.x <= Square.x + (100.0f * SquareScl.x) &&			//X座標
			Point.y >= Square.y - (100.0f * SquareScl.y) && Point.y <= Square.y + (100.0f * SquareScl.y) * 2 &&		//Y座標								//Y座標
			Point.z >= Square.z - (100.0f * SquareScl.z) && Point.z <= Square.z + (100.0f * SquareScl.z) &&			//Z座標
			Used == true)			//そのブロックが使われている
		{
			return true;		//ブロックの判定内にいる
		}
	}

	return false;		//ブロックの判定外にいる
}