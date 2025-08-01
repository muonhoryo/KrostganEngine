
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
	:GameObject(
		params.RenSprite->Tex,
		params.RenSprite->Offset, 
		params.Position, 
		params.Size, 
		GetSprColorFromFraction(params.EntityFraction),
		params.RenSprite->RenShader),
			ISelectableEntity(), 
		ICallbackRec_Upd(), 
		IFractionMember(),
		OrdersExecutor(
			*params.BattleStats, 
			nullptr, 
			nullptr),
		EntityFraction			(params.EntityFraction),
		HPBar					(params.HPBarSprite),
		SelectionSpriteSource	(params.SelectionSprite)

{
	params.Init_AAModule(*this);
	params.Init_AutoAggrModule(*this,GetActionsMediator());
	params.Init_DeathModule(*this);
	params.Init_HPModule();
	params.Init_HPRegenModule();
	SetAAModule(params.GetAAModule());
	SetAutoAggrModule(params.GetAutoAggrModule());
	HPModule = params.HPModule;

	SetPosition(GetPosition());
	SetScale(GetScale());
	SetColor(GetColor());

	EntitiesObserver::AddEntity(this);
}

Entity::~Entity() {
	SelectionOff();
	delete HPModule;
	if(SelectionSprite!=nullptr)
		delete SelectionSprite;
	delete HPBar;

	EntitiesObserver::RemoveEntity(this);
}

void Entity::SelectionOn() {
	if (!IsEntitySelected && !HPModule->DeathModule.GetIsDeadState()) {
		IsEntitySelected = true;
		SelectionSprite = new SingleSprite(
			SelectionSpriteSource->Tex,
			SelectionSpriteSource->MaxSize, 
			SelectionSpriteSource->Offset, 
			GetPosition(),
			GetScale(),
			GetColor());
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
	HPBar->SetPosition(position);
}
void Entity::SetScale(float scale) {
	GameObject::SetScale(scale);
	if (IsEntitySelected)
		SelectionSprite->SetScale(scale);
	HPBar->SetScale(scale);
}
void Entity::SetColor(Color color) {
	SpriteRenderer::SetColor(color);
	if(SelectionSprite!=nullptr)
		SelectionSprite->SetColor(color);
	HPBar->SetColor(color);
}

void Entity::RenderGraphic(RenderWindow& window) {

	if (!HPModule->DeathModule.GetIsDeadState()) {
		SingleSprite::RenderGraphic(window);
	}
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

IHitPointModule& Entity::GetHPModule() {
	return *HPModule;
}