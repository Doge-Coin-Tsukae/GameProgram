#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "human.h"

#include "model.h"
#include "sight.h"
#include "weapon.h"
#include "colider.h"
#include "enemy.h"
#include "base.h"
#include "enemycommander.h"

#define MAX_RESPORNTIME 240;

void CENEMY_COMMANDER::Init()
{
	resporn_timer = MAX_RESPORNTIME;
}
void CENEMY_COMMANDER::Uninit()
{

}
void CENEMY_COMMANDER::Update()
{

}