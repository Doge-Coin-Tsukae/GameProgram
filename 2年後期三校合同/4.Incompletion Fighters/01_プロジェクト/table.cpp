
#include "table.h"

D3DXVECTOR2 animeTable[11]=
{
	D3DXVECTOR2(0.0f, 0.0f),
	D3DXVECTOR2(0.2f, 0.0f),
	D3DXVECTOR2(0.4f, 0.0f),
	D3DXVECTOR2(0.6f, 0.0f),
	D3DXVECTOR2(0.8f, 0.0f),
	D3DXVECTOR2(1.0f, 0.0f),
	D3DXVECTOR2(1.2f, 0.0f),
	D3DXVECTOR2(1.4f, 0.0f),
	D3DXVECTOR2(1.6f, 0.0f),
	D3DXVECTOR2(1.8f, 0.0f),
	D3DXVECTOR2(2.0f, 0.0f),
};

D3DXVECTOR2 GetAnimTbl(int anim)
{
	return animeTable[anim];
}
