#pragma once

#include "gameobject.h"

//�~���m�̂����蔻��
class CCOLIDER_CIRCLE: public CGameObject
{
private:
	CModel *m_Model;				//���g�̃��f��

public:
	CCOLIDER_CIRCLE(){}
	~CCOLIDER_CIRCLE() {}

	void Init();		//�e�̃A�h���X������
	void Uninit();
	void Update();
	void Draw();
	bool GetColider(D3DXVECTOR3 pPos);		//�����蔻��K��(����̍��W) = �������Ă��邩�ۂ���Ԃ�
};

//Axis Aligned Bounding Box �̓����蔻��
struct AABB {
	D3DXVECTOR3 min;            //      �ő�l
	D3DXVECTOR3 max;            //      �ŏ��l
	D3DXVECTOR3 actorOldPos;         //      �O�̍��W�l
	AABB() = default;
	~AABB() = default;
	void Init(D3DXVECTOR3 minValue, D3DXVECTOR3 maxValue, D3DXVECTOR3 actorPos) {
		min = minValue;
		max = maxValue;
		actorOldPos = actorPos;
	}
	// �X�V
	void update(const D3DXVECTOR3& actorPosition) {
		D3DXVECTOR3 diff = actorPosition - actorOldPos;
		min += diff;
		max += diff;
		actorOldPos = actorPosition;
	}
};
// AABB��AABB�̏Փ˔���
inline bool intersectAABB(const AABB& box1, const AABB& box2) {
	if (box1.min.x > box2.max.x) return false;
	if (box1.max.x < box2.min.x) return false;
	if (box1.min.y > box2.max.y) return false;
	if (box1.max.y < box2.min.y) return false;
	if (box1.min.z > box2.max.z) return false;
	if (box1.max.z < box2.min.z) return false;
	return true;   // �ՓˁI�I
}

//OBB
class OBB : public CGameObject
{
private:

public:
	void Init(){}
	void Update(){}
	void parent(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl)
	{
		m_Position = pos;
		m_Rotation = rot;
		m_Scale = scl;
	}

	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 0.5f;
	}

	//������(Z)
	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		return vz * 0.5f;
	}

	//������(Y)
	D3DXVECTOR3 GetObbY()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		world = scale * rot;

		D3DXVECTOR3 vy;
		vy.x = world._21;
		vy.y = world._22;
		vy.z = world._23;

		return vy * 0.5f;
	}
	bool intersectOBB(const OBB& box1, const OBB& box2)
	{

		return false;
	}
};