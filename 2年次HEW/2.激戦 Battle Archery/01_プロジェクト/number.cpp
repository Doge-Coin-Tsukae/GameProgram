#include "texture.h"
#include "sprite.h"
#include "number.h"


void Number_Draw(float x, float y, int n,int player,int Size)
{
	if (n < 0 || n > 9) return;

	switch (n)
	{
	case 0:
		n = 9;
		break;
	case 1:
		n = 0;
		break;
	case 2:
		n = 1;
		break;
	case 3:
		n = 2;
		break;
	case 4:
		n = 3;
		break;
	case 5:
		n = 4;
		break;
	case 6:
		n = 5;
		break;
	case 7:
		n = 6;
		break;
	case 8:
		n = 7;
		break;
	case 9:
		n = 8;
		break;
	}

	//1P‚ÌŽž
	if (player == 0)
	{
		Sprite_Draw(TEXTURE_INDEX_NUMBER_RED,
			x, y,
			NUMBER_WIDTH * n, 0,
			NUMBER_WIDTH, NUMBER_HEIGHT);
	}
	else if(player ==1)
	{
		Sprite_Draw(TEXTURE_INDEX_NUMBER_BLUE,
			x, y,
			NUMBER_WIDTH * n, 0,
			NUMBER_WIDTH, NUMBER_HEIGHT);
	}
	else
	{
		Sprite_Draw(TEXTURE_INDEX_NUMBER,
			x, y,
			NUMBER_WIDTH * n, 0,
			NUMBER_WIDTH, NUMBER_HEIGHT);
	}
}