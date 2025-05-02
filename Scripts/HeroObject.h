#pragma once

#include <UnitObject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class HeroObject:UnitObject {
	public:
		HeroObject(EntityBattleStats& BattleStats,const Texture& RenTexture, Vector2f RenOffset, Vector2f Position, float Size);
		~HeroObject();

	protected:
		const Texture& GetSelectionTexture() override;
		float GetSelectSpriteMaxSize() override;
	};
}