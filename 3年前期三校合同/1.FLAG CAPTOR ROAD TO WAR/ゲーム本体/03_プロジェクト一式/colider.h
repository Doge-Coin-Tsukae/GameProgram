#pragma once

#include "gameobject.h"

//円同士のあたり判定
class CCOLIDER_CIRCLE: public CGameObject
{
private:
	CModel *m_Model;				//自身のモデル

public:
	CCOLIDER_CIRCLE(){}
	~CCOLIDER_CIRCLE() {}

	void Init();		//親のアドレスを入れる
	void Uninit();
	void Update();
	void Draw();
	bool GetColider(D3DXVECTOR3 pPos);		//当たり判定習得(判定の座標) = 当たっているか否かを返す
};

//Axis Aligned Bounding Box の当たり判定
struct AABB {
	D3DXVECTOR3 min;            //      最大値
	D3DXVECTOR3 max;            //      最小値
	D3DXVECTOR3 actorOldPos;         //      前の座標値
	AABB() = default;
	~AABB() = default;
	void Init(D3DXVECTOR3 minValue, D3DXVECTOR3 maxValue, D3DXVECTOR3 actorPos) {
		min = minValue;
		max = maxValue;
		actorOldPos = actorPos;
	}
	// 更新
	void update(const D3DXVECTOR3& actorPosition) {
		D3DXVECTOR3 diff = actorPosition - actorOldPos;
		min += diff;
		max += diff;
		actorOldPos = actorPosition;
	}
};
// AABBとAABBの衝突判定
inline bool intersectAABB(const AABB& box1, const AABB& box2) {
	if (box1.min.x > box2.max.x) return false;
	if (box1.max.x < box2.min.x) return false;
	if (box1.min.y > box2.max.y) return false;
	if (box1.max.y < box2.min.y) return false;
	if (box1.min.z > box2.max.z) return false;
	if (box1.max.z < box2.min.z) return false;
	return true;   // 衝突！！
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

	//分離軸(Z)
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

	//分離軸(Y)
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