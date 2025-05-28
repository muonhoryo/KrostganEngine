
#include <GameUI.h>

using namespace std;
using namespace KrostganEngine::UI;

//
// 
// Event subscribers
// 
//

OrderTargsVisManager::AddEntitySubscriber::AddEntitySubscriber(OrderTargsVisManager& Owner)
	:Owner(Owner) {
}

void OrderTargsVisManager::AddEntitySubscriber::Execute(ISelectableEntity* const& args) {
	Owner.TryInsertEntity(args);
}

OrderTargsVisManager::RemoveEntitySubscriber::RemoveEntitySubscriber(OrderTargsVisManager& Owner)
	:Owner(Owner) {
}

void OrderTargsVisManager::RemoveEntitySubscriber::Execute(ISelectableEntity* const& args) {
	Owner.TryRemoveEntity(args);
}

OrderTargsVisManager::ClearListSubscriber::ClearListSubscriber(OrderTargsVisManager& Owner)
	:Owner(Owner) {
}

void OrderTargsVisManager::ClearListSubscriber::Execute() {
	Owner.Clear();
}

//
//
// Class-container
// 
//

OrderTargsVisManager::OrderTargsVisManager() {
	Initialize_EntitiesTargetViss();
	AddSub = new AddEntitySubscriber(*this);
	RemSub = new RemoveEntitySubscriber(*this);
	ClearSub = new ClearListSubscriber(*this);
	GroupSelectionSystem::AddSelectableEvent.Add(AddSub);
	GroupSelectionSystem::RemoveSelectableEvent.Add(RemSub);
	GroupSelectionSystem::ClearSelectionEvent.Add(ClearSub);
}
OrderTargsVisManager::~OrderTargsVisManager() {
	GroupSelectionSystem::AddSelectableEvent.Remove(AddSub);
	GroupSelectionSystem::RemoveSelectableEvent.Remove(RemSub);
	GroupSelectionSystem::ClearSelectionEvent.Remove(ClearSub);
	Clear();
	delete AddSub;
	delete RemSub;
	delete ClearSub;
}

void OrderTargsVisManager::TryInsertEntity(ISelectableEntity* ent) {
	Entity* parArg = dynamic_cast<Entity*>(ent);
	if (parArg != nullptr) {
		EntitiesTargetViss.insert(pair<Entity*, OrderTargetsVisualizer*>(parArg, new OrderTargetsVisualizer(*parArg)));
	}
}
void OrderTargsVisManager::TryRemoveEntity(ISelectableEntity* ent) {
	Entity* parArg = dynamic_cast<Entity*>(ent);
	if (parArg != nullptr) {
		delete EntitiesTargetViss[parArg];
		EntitiesTargetViss.erase(parArg);
	}
}
void OrderTargsVisManager::Clear() {
	for (auto p : EntitiesTargetViss) {
		delete p.second;
	}
	EntitiesTargetViss.clear();
}

void OrderTargsVisManager::Initialize_EntitiesTargetViss() {
	EntitiesTargetViss = map<Entity*, OrderTargetsVisualizer*>();
	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	for (;begIt != endIt;++begIt) {
		TryInsertEntity(*begIt);
	}
}

IEventSubscriber<Entity*>* AddSub;
IEventSubscriber<Entity*>* RemSub;
INoArgsEventSubscriber* ClearSub;