
#include <Entity.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <list>
#include <IEntityOrder.h>
#include <IEntityAction.h>
#include <EntityHPModule.h>
#include <EntitiesObserver.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;

Entity::Entity(EntityCtorParams& params)
	:GameObject(params),
	ISelectableEntity(), 
	ICallbackRec_Upd(), 
	IFractionMember(),
	OrdersExecutor(
		*params.BattleStats, 
		nullptr, 
		nullptr),

	EntityFraction			(params.EntityFraction),
	HPBar					(params.HPBarSprite),
	SelectionSpriteSource	(params.SelectionSpriteSource)

{
	params.Init_AAModule(*this);
	params.Init_AutoAggrModule(*this,GetActionsMediator());
	params.Init_DeathModule(*this);
	params.Init_HPModule();
	params.Init_HPRegenModule();
	SetAAModule(params.GetAAModule());
	SetAutoAggrModule(params.GetAutoAggrModule());
	HPModule = params.HPModule;

	HPBar->SetGlobalPosition(GetGlobalPosition());
	HPBar->SetParent(this);
	SetColor(GetColor());

	EntitiesObserver::AddEntity(this);
}

Entity::~Entity() {
	SelectionOff();
	delete HPModule;

	EntitiesObserver::RemoveEntity(this);
}

void Entity::SetColor(Color color) {

	BodySprite.SetColor(color);
	if (SelectionSprite != nullptr)
		SelectionSprite->SetColor(color);
	HPBar->SetColor(color);
}

void Entity::SelectionOn() {

	if (!IsEntitySelected && !HPModule->DeathModule.GetIsDeadState()) {

		IsEntitySelected = true;
		SelectionSprite = new SquareScaleSprite(
			SelectionSpriteSource->Tex,
			*this,
			SelectionSpriteSource->MaxSize,
			Vector2f(0,0),
			1,
			GetColor(),
			nullptr);
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

void Entity::SetGlobalPosition(Vector2f position) {
	GameObject::SetGlobalPosition(position);
}
void Entity::SetGlobalScale(Vector2f scale) {
	GameObject::SetGlobalScale(scale);
}

void Entity::Update(CallbackRecArgs_LUpd args) {

	if (!HPModule->DeathModule.GetIsDeadState()) {
		DynamicPhysObject::Update(args);
	}
}
vector<IPhysicalObject*> Entity::OverlapAll() const {

	if (!HPModule->DeathModule.GetIsDeadState()) {
		return OverlapAll_Action();
	}
	else
		return vector<IPhysicalObject*>();
}
const ColliderShape& Entity::GetCollider() const {
	if (!HPModule->DeathModule.GetIsDeadState()) {
		return GetCollider_Action();
	}
	else
		return PhysicsEngine::EmptyCollInstance;
}

IHitPointModule& Entity::GetHPModule() const {
	return *HPModule;
}