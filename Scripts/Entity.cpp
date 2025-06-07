
#include <Entity.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <list>
#include <IEntityOrder.h>
#include <IEntityAction.h>
#include <EntityHPModule.h>
#include <GameObjectsManager.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

Entity::Entity(EntityCtorParams& params)
	:GameObject(*params.RenTexture, params.RenOffset, params.Position, params.Size, GetSprColorFromFraction(params.EntityFraction)),
	ISelectableEntity(), ICallbackRec_Upd(), IFractionMember(),
	OrdersExecutor(*params.BattleStats, nullptr, nullptr)
{
	params.Init_AAModule(*this);
	params.Init_AutoAggrModule(*this,GetActionsMediator());
	params.Init_HPModule();
	SetAAModule(params.GetAAModule());
	SetAutoAggrModule(params.GetAutoAggrModule());
	HPModule = params.HPModule;

	this->EntityFraction = params.EntityFraction;
	IsEntitySelected = false;
	SelectionSprite = nullptr;

	GameObjectsManager::AddEntity(this);
}

Entity::~Entity() {
	SelectionOff();
}

void Entity::SelectionOn() {
	if (!IsEntitySelected) {
		IsEntitySelected = true;
		SelectionSprite = new SingleSprite(GetSelectionTexture(), GetSelectSpriteMaxSize(), GetSelectSpriteRenOffset(), 
			GetPosition(), GetScale(),GetSpriteColor());
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
void Entity::SetSpriteColor(Color color) {
	SpriteRenderer::SetSpriteColor(color);
	SelectionSprite->SetSpriteColor(color);
}

IHitPointModule& Entity::GetHPModule() {
	return *HPModule;
}