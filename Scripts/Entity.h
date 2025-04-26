#pragma once

#include <Gameobject.h>
#include <EntitiesControl.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SingleSprite.h>

using namespace sf;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	class Entity :public GameObject,public ISelectableEntity{
	public:
		~Entity();

		void SelectionOn() override;
		void SelectionOff() override;
		bool IsSelected() override;

		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;

	protected:
		Entity(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position, float Size);

		virtual const Texture& GetSelectionTexture()=0;
		virtual float GetSelectSpriteMaxSize() = 0;
		virtual Vector2f GetSelectSpriteRenOffset() { return Vector2f(0, 0); };

	private:
		bool IsEntitySelected;
		SingleSprite* SelectionSprite;
	};
}