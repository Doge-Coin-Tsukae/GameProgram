//****************************************************
//�x�N�g���v�Z�̃v���O����
//****************************************************

#include "Vector.h"
#include "myDirect3D.h"

//*****************************************************************************
//�v���O����
//*****************************************************************************

//�P�ʃx�N�g�����擾����
D3DXVECTOR3 GetVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 Vector;

	D3DXVECTOR3 xyz = start - end;

	//�x�N�g�������
	float l = sqrt((xyz.x*xyz.x) + (xyz.y*xyz.y) + (xyz.z*xyz.z));

	//�P�ʃx�N�g�������
	Vector = -(xyz / l);

	return Vector;
}