
#include <UnitObject.h>
#include <GameVisualEffects.h>
#include <Engine.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine;

void UnitDeathModule::Death() {

	auto dSprRes = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(ExternalGlobalResources::CORE_RES_UNIT_DEATHEFFECT);
	auto dSpr = new SpriteRenderer(
		dSprRes->Tex,
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		dSprRes->RenShader);
	dSpr->SetColor(dynamic_cast<UnitObject*>(&Owner)->GetColor());
	dSpr->AddEffect(*new FadingVisualEff_Des(Engine::GetGlobalConsts().AverageLifeTime_DeathEffect, *dSpr));
	EntityDeathModule::Death();
}