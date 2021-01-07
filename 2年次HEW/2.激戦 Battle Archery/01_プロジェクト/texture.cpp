#include <d3dx9.h>
#include "mydirect3d.h"
#include "texture.h"

#define TEXTURE_FILENAME_MAX (64)		//テクスチャの文字列

typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];		//ファイルのパス名
	int width;									//横幅
	int height;									//縦幅
} TextureFile;

static const TextureFile g_TextureFiles[] = {
	{ "asset/texture/number/number.png",320,32},
	{ "asset/texture/number/number_blue.png",320,32},
	{ "asset/texture/number/number_red.png",320,32},
	{ "asset/texture/scene/selectcharasoto.png", 1280, 720 },
	{ "asset/texture/selectcharacursor1P.png", 590, 230 },
	{ "asset/texture/selectcharacursor2P.png", 590, 230 },
	{ "asset/texture/sight/40%.png", 128, 128 },
	{ "asset/texture/background/venue.png",1500,750},
	{ "asset/texture/number/count.png",575,200},
	{ "asset/texture/number/start.png",550,100},
	{ "asset/texture/number/time up.png",550,100},
	{ "asset/texture/number/1p.png",70,51},
	{ "asset/texture/number/2p.png",70,51},
	{ "asset/texture/number/4p.png",70,51},
	{ "asset/texture/number/win.png",600,115},
	{ "asset/texture/number/draw.png",400,107},
	{ "asset/texture/number/play_2.png",100,55},
	{ "asset/texture/gauge/arrowpowar.png",350,30},
	{ "asset/texture/gauge/arrowpowarbox.png",350,30},
	{ "asset/texture/result_bar.png",1600,200},
	{ "asset/texture/title_2.png",765,480},
	{ "asset/texture/national_flag/jpn.png",590,230},
	{ "asset/texture/national_flag/usa.png",590,230},
	{ "asset/texture/national_flag/kor.png",590,230},
	{ "asset/texture/national_flag/fra.png",590,230},
	{ "asset/texture/number/chose.png",1000,100},
	{ "asset/texture/background/kussa1.jpg",149,149},
	{ "asset/texture/explain1.png",1400,300},
	{ "asset/texture/logo1.png",1300,500},

};

static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);

static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};

int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	/*for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            //DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}*/

	return failed_count;
}

void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].width;
}

int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].height;
}

//テクスチャの個別セット
void SetTexture(TextureIndex index)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXCreateTextureFromFile(pDevice, g_TextureFiles[index].filename, &g_pTextures[index]);
}
//テクスチャの個別解放
void ReleaseTexture(TextureIndex index)
{
	if (g_pTextures[index]) {
		g_pTextures[index]->Release();
		g_pTextures[index] = NULL;
	}
}