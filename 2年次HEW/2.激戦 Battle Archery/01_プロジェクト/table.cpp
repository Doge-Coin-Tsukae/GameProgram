
#include "table.h"

D3DXVECTOR2 animeTable[3]=
{
	D3DXVECTOR2(1.51f,  0.0f),
	D3DXVECTOR2(0.8f, 0.0f),
	D3DXVECTOR2(0.0f, 0.0f),
	
	
};

D3DXVECTOR2 GetAnimTbl(int anim)
{
	return animeTable[anim];
}
