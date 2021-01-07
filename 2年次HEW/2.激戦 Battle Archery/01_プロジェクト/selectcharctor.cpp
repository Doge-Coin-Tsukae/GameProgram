//****************************************************
//キャラ選択画面のプログラム
//****************************************************


#include "input.h"
#include "scene.h"
#include "score_draw.h"
#include "sprite.h"
#include "sound.h"
#include "texture.h"
#include "fade.h"
#include "tittle_camera.h"
#include "player.h"
#include "x_gamepad.h"

static bool g_bEnd = false;

static int country[2][2]; 	//メニュー画面にある国の個数
int countrydata[2];	//プレイヤーが選んだ物を入れる
static int cursor_x[2];		//カーソルx座標
static int cursor_y[2];		//カーソルy座標
static int SetChar;			//1P2Pが押したら進める
static bool LockChar[2];	//国選択したら二度漬けさせないためにロックを掛ける

void SelectChar_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));

	TCamera_Initialize();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			country[i][j] = (i * 2) + j;			//右上から0,1,2,3のように並んでいる
		}

		cursor_x[i] = i;
		cursor_y[i] = 0;
		LockChar[i] = false;
	}

	SetChar = 0;
	g_bEnd = false;

	SetTexture(TEXTURE_INDEX_CHOSE);
	SetTexture(TEXTURE_INDEX_FLAG_JPN);
	SetTexture(TEXTURE_INDEX_FLAG_USA);
	SetTexture(TEXTURE_INDEX_FLAG_FRA);
	SetTexture(TEXTURE_INDEX_FLAG_KOR);
	SetTexture(TEXTURE_INDEX_SELECTCORSOR1P);
	SetTexture(TEXTURE_INDEX_SELECTCORSOR2P);
}

void SelectChar_Finalize(void)
{
	TCamera_Finalize();

	ReleaseTexture(TEXTURE_INDEX_CHOSE);
	ReleaseTexture(TEXTURE_INDEX_FLAG_JPN);
	ReleaseTexture(TEXTURE_INDEX_FLAG_USA);
	ReleaseTexture(TEXTURE_INDEX_FLAG_FRA);
	ReleaseTexture(TEXTURE_INDEX_FLAG_KOR);
	ReleaseTexture(TEXTURE_INDEX_SELECTCORSOR1P);
	ReleaseTexture(TEXTURE_INDEX_SELECTCORSOR2P);
}

void SelectChar_Update(void)
{
	TCamera_Update();

	if (!g_bEnd) {
		//十字移動で選ぶ(1P)
		{
			if (LockChar[0] == false)
			{
				if (Keyboard_IsTrigger(DIK_W) || gamepad_inport(0, PP_LY) >= 10000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_y[0] > 0)
					{
						cursor_y[0]--;
					}
					else if (cursor_y[0] == 0)
					{ 
						cursor_y[0] = 1;
					}
				}
				if (Keyboard_IsTrigger(DIK_S) || gamepad_inport(0, PP_LY) <= -10000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_y[0] < 1)
					{
						cursor_y[0]++;
					}
					else if (cursor_y[0] = 1)
					{
						cursor_y[0] = 0;
					}
				}
				if (Keyboard_IsTrigger(DIK_A) || gamepad_inport(0, PP_LX) <= -5000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_x[0] > 0)
					{
						cursor_x[0]--;
					}
					else if (cursor_x[0] == 0)
					{
						cursor_x[0] = 1;
					}
				}
				if (Keyboard_IsTrigger(DIK_D) || gamepad_inport(0, PP_LX) >= 5000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_x[0] < 1)
					{
						cursor_x[0]++;
					}
					else if (cursor_x[0] == 1)
					{
						cursor_x[0] = 0;
					}
				}
			}
		}

		//十字移動で選ぶ(2P)
		{
			if (LockChar[1] == false)
			{
				if (Keyboard_IsTrigger(DIK_I) || gamepad_inport(1, PP_LY) >= 10000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_y[1] > 0)
					{
						cursor_y[1]--;
					}
					else if (cursor_y[1] == 0)
					{
						cursor_y[1] = 1;
					}
				}
				if (Keyboard_IsTrigger(DIK_K) || gamepad_inport(1, PP_LY) <= -10000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_y[1] < 1)
					{
						cursor_y[1]++;
					}
					else if (cursor_y[1] == 1)
					{
						cursor_y[1] = 0;
					}
				}
				if (Keyboard_IsTrigger(DIK_J) || gamepad_inport(1, PP_LX) <= -5000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_x[1] > 0)
					{
						cursor_x[1]--;
					}
					else if (cursor_x[1] == 0)
					{
						cursor_x[1] = 1;
					}
				}
				if (Keyboard_IsTrigger(DIK_L) || gamepad_inport(1, PP_LX) >= 5000)
				{
					PlaySound(SOUND_LABEL_SE_POINT_SELECT);
					if (cursor_x[1] < 1)
					{
						cursor_x[1]++;
					}
					else if (cursor_x[1] == 1)
					{
						cursor_x[1] = 0;
					}
				}
			}
		}

		//スペースキーで1Pのキャラ決定
		if (Keyboard_IsTrigger(DIK_SPACE) || gamepad_inport(0, PP_A))
		{
			PlaySound(SOUND_LABEL_SE_SELECT_DECISION);
			if (LockChar[0] == false)
			{
				countrydata[0] = country[cursor_x[0]][cursor_y[0]];	//選んだ国データを入れる
				SetChar++;											//セット数を1増やす
				LockChar[0] = true;
			}
		}

		//スペースキーで2Pのキャラ決定
		if (Keyboard_IsTrigger(DIK_O) || gamepad_inport(1, PP_A))
		{
			PlaySound(SOUND_LABEL_SE_SELECT_DECISION);
			if (LockChar[1] == false)
			{
				countrydata[1] = country[cursor_x[1]][cursor_y[1]];	//選んだ国データを入れる
				SetChar++;											//セット数を1増やす
				LockChar[1] = true;
			}
		}

		//2人のキャラが決定したら画面ワープ
		if (SetChar > 1)
		{
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
			StopSound(SOUND_LABEL_TITLE_BGM);
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_TUTORIAL);
		}
	}
}

void SelectChar_Draw(void)
{
	// 1P画面
	for (int i = 0; i < MAX_PLAYER; i++)
	{
		TCamera_SetCamera(i);

		// choose your coutry
		Sprite_Draw(TEXTURE_INDEX_CHOSE, 290.0f + (i*1510), 50.0f);

		// 国旗l
		Sprite_Draw(TEXTURE_INDEX_FLAG_JPN, 180.0f + (i * 1510), 210.0f);
		Sprite_Draw(TEXTURE_INDEX_FLAG_USA, 850.0f + (i * 1510), 212.0f);
		Sprite_Draw(TEXTURE_INDEX_FLAG_FRA, 180.0f + (i * 1510), 470.0f);
		Sprite_Draw(TEXTURE_INDEX_FLAG_KOR, 850.0f + (i * 1510), 472.0f);


		Sprite_Draw(TEXTURE_INDEX_SELECTCORSOR1P, 180.0f + (i * 1510) + 670.0f * cursor_x[0], 210.0f + 263.0f * cursor_y[0]);
		Sprite_Draw(TEXTURE_INDEX_SELECTCORSOR2P, 180.0f + (i * 1510) + 670.0f * cursor_x[1], 210.0f + 263.0f * cursor_y[1]);

		Fade_Draw();
	}
}

//ゲッター
int GetCharaData(int index)
{
	return countrydata[index];
}