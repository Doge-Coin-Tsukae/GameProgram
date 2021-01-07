#include "scene.h"
#include "logo.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "Tutorial.h"
#include "selectcharctor.h"

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;

typedef void(*SceneFunc)(void);

static const SceneFunc Initialize[] = {
	Logo_Initialize,
	Title_Initialize,
	SelectChar_Initialize,
	Tutorial_Initialize,
	Game_Initialize,
	Result_Initialize,
};


void Scene_Initialize(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;

	Initialize[g_SceneIndex]();
}

void Scene_Finalize(void)
{
	switch (g_SceneIndex) {

	case SCENE_INDEX_LOGO:
		Logo_Finalize();
		break;

	case SCENE_INDEX_TITLE:
		Title_Finalize();
		break;

	case SCENE_INDEX_SELECTCHAR:
		SelectChar_Finalize();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Finalize();
		break;

	case SCENE_INDEX_2PGAME:
		Game_Finalize();
		break;

	case SCENE_INDEX_RESULT:
		Result_Finalize();
		break;
	}
}

void Scene_Update(void)
{
	switch (g_SceneIndex) {

	case SCENE_INDEX_LOGO:
		Logo_Update();
		break;

	case SCENE_INDEX_TITLE:
		Title_Update();
		break;

	case SCENE_INDEX_SELECTCHAR:
		SelectChar_Update();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Update();
		break;

	case SCENE_INDEX_2PGAME:
		Game_Update();
		break;

	case SCENE_INDEX_RESULT:
		Result_Update();
		break;
	}
}

void Scene_Draw(void)
{
	switch (g_SceneIndex) {

	case SCENE_INDEX_LOGO:
		Logo_Draw();
		break;

	case SCENE_INDEX_TITLE:
		Title_Draw();
		break;

	case SCENE_INDEX_SELECTCHAR:
		SelectChar_Draw();
		break;

	case SCENE_INDEX_TUTORIAL:
		Tutorial_Draw();
		break;

	case SCENE_INDEX_2PGAME:
		Game_Draw();
		break;

	case SCENE_INDEX_RESULT:
		Result_Draw();
		break;
	}
}

void Scene_Check(void)
{
	if (g_SceneIndex != g_SceneNextIndex) {
		Scene_Finalize();
		Scene_Initialize(g_SceneNextIndex);
	}
}

void Scene_Change(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}
