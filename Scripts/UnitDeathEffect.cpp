
#include <UnitDeathEffect.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::GameObjects;

UnitDeathEffect::UnitDeathEffect(float LifeTime, Vector2f RenOffset,Vector2f Position, float Size, Color SprColor)
	:SingleSprite(ExternalGlobalResources::Get_UnitDeathEffect_Tex(),
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		RenOffset,
		Position,
		Size,
		SprColor),
	LifeTime(LifeTime){

	HidingTimer.restart();
}
UnitDeathEffect::UnitDeathEffect(UnitObject& Owner, Vector2f RenOffset)
	: UnitDeathEffect(Engine::GetGlobalConsts().AverageLifeTime_DeathEffect,
		RenOffset,
		Owner.GetPosition(),
		1,
		FractionsSystem::GetRelationColor(FractionsSystem::GetRelation(Fraction::Player,Owner.GetFraction()))){
}

void UnitDeathEffect::RenderGraphic(RenderWindow& window) {

	float time = HidingTimer.getElapsedTime().asSeconds();
	if (time < LifeTime) {

		float transparency = (LifeTime - time) / LifeTime;
		Color clr = GetSpriteColor();
		clr = Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255));
		SetSpriteColor(clr);
		SingleSprite::RenderGraphic(window);
	}
	else {
		SetSpriteColor(Color::Transparent);
		delete this;
	}
}