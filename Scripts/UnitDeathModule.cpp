
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
	auto unitOwner = dynamic_cast<UnitObject*>(&Owner);
	auto color = unitOwner->GetColor();
	dSpr->SetColor(color);
	dSpr->SetGlobalScale_Sng(unitOwner->GetGlobalScale_Sng() * dSpr->GetGlobalScale_Sng());
	dSpr->SetGlobalPosition(unitOwner->GetGlobalPosition());
	auto& eff = *new FadingVisualEff_Des(Engine::GetGlobalConsts().AverageLifeTime_DeathEffect, *dSpr);
	dSpr->AddEffect(eff);
	EntityDeathModule::Death();
}