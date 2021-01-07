//****************************************************
//�����蔻��̃v���O����
//****************************************************

#include "colision.h"
#include "myDirect3D.h"

//*****************************************************************************
//�v���O����
//*****************************************************************************

//�~�Ɠ_�̓����蔻��(�~�̍��W,�_�̍��W,���a)
bool CircleAndPoint(D3DXVECTOR3 pos, D3DXVECTOR3 epos,float radius)
{
	//�x�N�g��
	D3DXVECTOR3 xyz;
	//�P�ʃx�N�g��
	float vector;

	//�~�̒��S - �_
	xyz = pos - epos;
	vector = sqrt((xyz.x * xyz.x) + (xyz.y * xyz.y) + (xyz.z * xyz.z));

	if (sqrt(vector*vector)<=radius)
	{
		return true;
	}

	return false;
}

//�_�Ǝl�p�̓����蔻��
bool PointtoSquare(D3DXVECTOR3 Point,D3DXVECTOR3 Square,D3DXVECTOR3 SquareScl,int rupe,bool Used)
{
	for (int i = 0; i < rupe; i++)
	{
		if (Point.x >= Square.x - (100.0f * SquareScl.x) && Point.x <= Square.x + (100.0f * SquareScl.x) &&			//X���W
			Point.y >= Square.y - (100.0f * SquareScl.y) && Point.y <= Square.y + (100.0f * SquareScl.y) * 2 &&		//Y���W								//Y���W
			Point.z >= Square.z - (100.0f * SquareScl.z) && Point.z <= Square.z + (100.0f * SquareScl.z) &&			//Z���W
			Used == true)			//���̃u���b�N���g���Ă���
		{
			return true;		//�u���b�N�̔�����ɂ���
		}
	}

	return false;		//�u���b�N�̔���O�ɂ���
}