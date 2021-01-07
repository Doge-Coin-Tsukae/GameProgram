#pragma once

#include "gameobject.h"

#define FIELDX 300
#define FIELDY 300

class CMeshField : public CGameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture[2];

	VERTEX_3D					m_Vertex[FIELDX][FIELDY];

	int seed,oldseed;

	//ダイアモンドスクエア
	void diamondSquare(float Array[FIELDX][FIELDY], int size)
	{
		int half = size / 2;
		if (half < 1)
			return;
		//square steps
		for (int z = half; z < FIELDY; z += size)
			for (int x = half; x < FIELDX; x += size)
				squareStep(Array, x % FIELDX, z % FIELDY, half);
		// diamond steps
		int col = 0;
		for (int x = 0; x < FIELDX; x += half)
		{
			col++;
			//If this is an odd column.
			if (col % 2 == 1)
				for (int z = half; z < FIELDY; z += size)
					diamondStep(Array, x % FIELDX, z % FIELDY, half);
			else
				for (int z = 0; z < FIELDY; z += size)
					diamondStep(Array, x % FIELDX, z % FIELDY, half);
		}
		diamondSquare(Array, size / 2);
	}
	void squareStep(float Array[FIELDX][FIELDY], int x, int z, int reach)
	{
		int count = 0;
		float avg = 0.0f;
		if (x - reach >= 0 && z - reach >= 0)
		{
			avg += Array[x - reach][z - reach];
			count++;
		}
		if (x - reach >= 0 && z + reach < FIELDY)
		{
			avg += Array[x - reach][z + reach];
			count++;
		}
		if (x + reach < FIELDX && z - reach >= 0)
		{
			avg += Array[x + reach][z - reach];
			count++;
		}
		if (x + reach < FIELDX && z + reach < FIELDY)
		{
			avg += Array[x + reach][z + reach];
			count++;
		}
		avg += random(reach);
		avg /= count;
		Array[x][z] = round(avg);
	}
	void diamondStep(float Array[FIELDX][FIELDY], int x, int z, int reach)
	{
		int count = 0;
		float avg = 0.0f;
		if (x - reach >= 0)
		{
			avg += Array[x - reach][z];
			count++;
		}
		if (x + reach < FIELDX)
		{
			avg += Array[x + reach][z];
			count++;
		}
		if (z - reach >= 0)
		{
			avg += Array[x][z - reach];
			count++;
		}
		if (z + reach < FIELDY)
		{
			avg += Array[x][z + reach];
			count++;
		}
		avg += random(reach);
		avg /= count;
		Array[x][z] = avg;
	}
	inline static float random(int range)
	{
		//デフォ = (rand() % (range * 2)) - range;
		return (rand() % (range * 4)) - range;
	}

	void UpdateSeed();		//地形生成
	void TextureMixed();
public:
	CMeshField() {}
	~CMeshField() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(D3DXVECTOR3 Position);
	void flatworld();
};