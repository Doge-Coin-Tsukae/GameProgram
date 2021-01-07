#include "texture.h"
#include "sprite.h"
#include "countdown.h"


void Count_Draw(float x, float y, int n)
{
	if (n < 0 || n > 2) return;

	switch (n)
	{
	case 0:
		n = 0;
		break;
	case 1:
		n = 1;
		break;
	case 2:
		n = 2;
		break;
	
	}
}