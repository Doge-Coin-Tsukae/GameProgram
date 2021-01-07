//****************************************************
//�x�N�g���v�Z�̃v���O����
//****************************************************
#include "main.h"
#include "Vector.h"

//�P�ʃx�N�g�����擾����
D3DXVECTOR3 GetVector(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 Vector;

	D3DXVECTOR3 xyz = start - end;

	//�x�N�g�������
	double l = sqrt((xyz.x*xyz.x) + (xyz.y*xyz.y) + (xyz.z*xyz.z));

	//�P�ʃx�N�g�������
	Vector = -(xyz / l);

	return Vector;
}