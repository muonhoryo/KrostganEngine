
#include <Entity.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <list>
#include <IEntityOrder.h>
#include <IEntityAction.h>
#include <EntityHPModule.h>
#include <EntitiesObserver.h>

#include <ObservingArea.h>

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
	IWarFogObserver(FractionsSystem::GetRelationToPlayer(params.EntityFraction)==Relation::Ally),	//Entity observs war fog only when it is ally to player

	EntityFraction			(params.EntityFraction),
	HPBar					(params.HPBarSprite),
	HitEffectSprite			(params.HitEffectSprite),
	SelectionSpriteSource	(params.SelectionSpriteSource)

{
	params.Owner = this;
	params.Init_AAModule();
	params.Init_AutoAggrModule(GetActionsMediator());
	params.Init_DeathModule();
	params.Init_HPModule();
	params.Init_HPRegenModule();
	SetAAModule(params.GetAAModule());
	SetAutoAggrModule(params.GetAutoAggrModule());
	HPModule = params.HPModule;

	HPBar->SetGlobalPosition(GetGlobalPosition());
	HPBar->SetParent(this);

	HitEffectSprite->SetGlobalPosition(GetGlobalPosition());
	HitEffectSprite->SetParent(this);

	SetColor(GetColor());

	EntitiesObserver::AddEntity(this);

	BodySprite.Set_IsHidenByWarFog(true);
	HPBar->Set_IsHidenByWarFog(true);
	HitEffectSprite->Set_IsHidenByWarFog(true);
}

Entity::~Entity() {
	delete HPModule;

	EntitiesObserver::RemoveEntity(this);
}

void Entity::SetColor(Color color) {

	Color totalColor = color;
	color.a = BodySprite.GetColor().a;
	BodySprite.SetColor(totalColor);
	if (SelectionSprite != nullptr) {
		totalColor.a = SelectionSprite->GetColor().a;
		SelectionSprite->SetColor(totalColor);
	}
	totalColor.a = HitEffectSprite->GetColor().a;
	HitEffectSprite->SetColor(totalColor);
	totalColor.a = HPBar->GetColor().a;
	HPBar->SetColor(totalColor);
}

void Entity::SelectionOn() {

	if (!IsEntitySelected && !HPModule->DeathModule.GetIsDeadState()) {

		IsEntitySelected = true;
		SelectionSprite = new SpriteRenderer(
			SelectionSpriteSource->Tex,
			*this,
			SelectionSpriteSource->MaxSize,
			nullptr);
		SelectionSprite->SetColor(GetColor());
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
bool Entity::IsTargetableForAA() const {
	return GetBattleStats().GetState_IsTargetableForAA();
}

void Entity::SetTargetableForAA(bool isTargetable) {
	GetBattleStats().SetTargetableForAA(isTargetable);
}

float Entity::GetObservingRange() const {
	return GetBattleStats().GetObservingRange().Stat;
}