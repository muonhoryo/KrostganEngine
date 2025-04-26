
#include <Entity.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <GameObject.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

Entity::Entity(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position, float Scale)
	:GameObject(RenTexture,RenOffset,Position, Scale){
	IsEntitySelected = false;
	SelectionSprite = nullptr;
}
Entity::~Entity() {
	SelectionOff();
}

void Entity::SelectionOn() {
	if (!IsEntitySelected) {
		IsEntitySelected = true;
		SelectionSprite = new SingleSprite(GetSelectionTexture(), GetSelectSpriteMaxSize(), GetSelectSpriteRenOffset(), 
			GetPosition(), GetScale());
	}
}
void Entity::SelectionOff() {
	if (IsEntitySelected) {
		IsEntitySelected = false;
		if (SelectionSprite != nullptr)
		{
			delete SelectionSprite;
			SelectionSprite = nullptr;
		}
	}
}
bool Entity::IsSelected() {
	return IsEntitySelected;
}

void Entity::SetPosition(Vector2f position) {
	GameObject::SetPosition(position);
	if (IsEntitySelected)
		SelectionSprite->SetPosition(position);
}
void Entity::SetScale(float scale) {
	GameObject::SetScale(scale);
	if (IsEntitySelected)
		SelectionSprite->SetScale(scale);
}