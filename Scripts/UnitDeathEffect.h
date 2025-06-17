#pragma once

#include <CoreVisual.h>
#include <UnitObject.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class UnitDeathEffect : public SingleSprite {
	public:
		UnitDeathEffect(float LifeTime,Vector2f RenOffset = Vector2f(0, 0),
			Vector2f Position = Vector2f(0, 0), 
			float Size = 1, 
			Color SprColor = Color::White);
		UnitDeathEffect(UnitObject& Owner, Vector2f RenOffset=Vector2f(0,0));

		void RenderGraphic(RenderWindow& window) override;

	private:
		Clock HidingTimer;
		float LifeTime = 0;
	};
}