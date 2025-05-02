
#include <Entity.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <GameObject.h>
#include <list>
#include <IEntityOrder.h>
#include <IEntityAction.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

Entity::Entity(EntityBattleStats& BattleStats,const Texture& RenTexture, Vector2f RenOffset, Vector2f Position, float Scale)
	:GameObject(RenTexture,RenOffset,Position, Scale), ISelectableEntity(),ICallbackRec_Upd(),
	BattleStats(BattleStats){
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
	OrdersTargetsVisualizer->SetPointPosition(position, 0);
}
void Entity::SetScale(float scale) {
	GameObject::SetScale(scale);
	if (IsEntitySelected)
		SelectionSprite->SetScale(scale);
}