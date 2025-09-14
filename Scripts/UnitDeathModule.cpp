
#include <UnitObject.h>
#include <GameVisualEffects.h>
#include <Engine.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine;

void UnitDeathModule::Death() {

	auto dSprRes = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(ExternalGlobalResources::CORE_RES_UNIT_DEATHEFFECT);
	auto dSpr = new SquareScaleSprite(
		dSprRes->Tex,
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		Vector2f(0,0),
		1,
		dynamic_cast<UnitObject*>(&Owner)->GetColor(),
		dSprRes->RenShader);
	dSpr->AddEffect(*new FadingVisualEff_Des(Engine::GetGlobalConsts().AverageLifeTime_DeathEffect, *dSpr));
	EntityDeathModule::Death();
}