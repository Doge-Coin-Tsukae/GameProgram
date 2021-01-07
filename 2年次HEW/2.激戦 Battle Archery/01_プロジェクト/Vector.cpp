//****************************************************
//ベクトル計算のプログラム
//****************************************************

#include "Vector.h"
#include "myDirect3D.h"

//*****************************************************************************
//プログラム
//*****************************************************************************

//単位ベクトルを取得する
D3DXVECTOR3 GetVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 Vector;

	D3DXVECTOR3 xyz = start - end;

	//ベクトルを取る
	float l = sqrt((xyz.x*xyz.x) + (xyz.y*xyz.y) + (xyz.z*xyz.z));

	//単位ベクトルを取る
	Vector = -(xyz / l);

	return Vector;
}