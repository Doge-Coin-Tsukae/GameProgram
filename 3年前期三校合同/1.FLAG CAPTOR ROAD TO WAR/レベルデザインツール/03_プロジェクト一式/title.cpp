#include <list>
#include <vector>
#include <typeinfo>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gamemaneger.h"
#include "Title.h"
#include "Game.h"

void CTitle::Init()
{

}

void CTitle::Update()
{
	CScene::Update();

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CManager::SetScene<CGame>();
	}
}