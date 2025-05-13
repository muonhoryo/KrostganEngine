
#include <Entity.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <list>
#include <IEntityOrder.h>
#include <IEntityAction.h>
#include <EntityHPModule.h>
#include <EntityBaseAAModule.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

Entity::Entity(EntityBattleStats& BattleStats,Fraction EntityFraction,const Texture& RenTexture, Vector2f RenOffset, Vector2f Position, float Scale)
	:GameObject(RenTexture,RenOffset,Position, Scale,GetSprColorFromFraction(EntityFraction)), ISelectableEntity(),ICallbackRec_Upd(),IFractionMember(),
	BattleStats(BattleStats),
	HPModule(*new EntityHPModule(BattleStats)),
	AAModule(*new EntityBaseAAModule(BattleStats,*this))
{
	this->EntityFraction = EntityFraction;
	IsEntitySelected = false;
	SelectionSprite = nullptr;

	OrdersQueue = list<IEntityOrder*>();
	ActionsToExecute = new list<IEntityAction*>();
	CurrentOrder = nullptr;
	CurrentActionToExecute = nullptr;
	vector<Vector2f>& pointsForVis = *new vector<Vector2f>{ GetPosition() };
	OrdersTargetsVisualizer = new LinesVisPrimitive(pointsForVis,Color::Green);
	delete &pointsForVis;
}
Entity::~Entity() {
	SelectionOff();

	if (ActionsToExecute != nullptr)
		delete ActionsToExecute;
	OrdersQueue.clear();
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
	OrdersTargetsVisualizer->SetPointPosition(position, 0);
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

TransformableObj& Entity::GetTransform() {
	return *(TransformableObj*)this;
}

const EntityBattleStats& Entity::GetBattleStats() {
	return BattleStats;
}
IHitPointModule& Entity::GetHPModule() {
	return HPModule;
}
AutoAttackModule& Entity::GetAAModule() {
	return AAModule;
}