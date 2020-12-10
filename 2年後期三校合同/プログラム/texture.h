#pragma once

#include <d3d9.h>

typedef enum 
{
    TEXTURE_INDEX_FIELD01,
	TEXTURE_INDEX_FIELD02,
	TEXTURE_INDEX_HPBARBOX,
	TEXTURE_INDEX_HP,
	TEXTURE_INDEX_WINMARK,
	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_RESULT,
	TEXTURE_INDEX_TUTORIAL,
	TEXTURE_INDEX_1P,
	TEXTURE_INDEX_2P,
	TEXTURE_INDEX_WINNER,
    TEXTURE_INDEX_MAX
}TextureIndex;

int Texture_Load(void); //������
void Texture_Release(void); //�I������
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);
int Texture_GetWidth(TextureIndex index);
int Texture_GetHeight(TextureIndex index);
