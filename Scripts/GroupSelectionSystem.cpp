#pragma once

#include <ISelectableEntity.h>
#include <GroupSelectionSystem.h>
#include <iostream>
#include <GameObject.h>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

GroupSelectionSystem::GroupSelectionSystem(){
	Singleton = this;
	SelEntsRelationToPl = FractionsSystem::DefaultRel;
}
GroupSelectionSystem::~GroupSelectionSystem() {
	Singleton = nullptr;
}

GroupSelectionSystem& GroupSelectionSystem::GetInstance() {
	if (GroupSelectionSystem::Singleton == nullptr)
		new GroupSelectionSystem();
	return *GroupSelectionSystem::Singleton;
}

void GroupSelectionSystem::Add(ISelectableEntity*& entity) {
	
	// Check relation of entity to player for not allowing selection more than one of not ally entity
	ptrdiff_t size = distance(Singleton->SelectedEntities.begin(), Singleton->SelectedEntities.end());
	IFractionMember* fracEnt = dynamic_cast<IFractionMember*>(entity);
	Fraction frac = fracEnt == nullptr ? FractionsSystem::DefaultFrac : fracEnt->GetFraction();
	Relation rel = FractionsSystem::GetRelation(frac, Fraction::Player);
	if (size == 0) {
		Singleton->SelEntsRelationToPl = rel;
	}
	else if (rel==Relation::Ally){
		if (Singleton->SelEntsRelationToPl != Relation::Ally) {
			Clear();
			Singleton->SelEntsRelationToPl = rel;
		}
	}
	else {
		return;
	}
	// Check relation of entity to player for not allowing selection more than one of not ally entity

	Singleton->SelectedEntities.push_front(entity);
	entity->SelectionOn();
	Singleton->AddSelectableEventHandler.Execute(entity);

	GameObject* ref = dynamic_cast<GameObject*>(entity);
	if (ref != nullptr) {
		cout <<ToString(ref->GetSpriteGlobalPosition()) << endl;
	}
	else {
		cout << " null " << endl;
	}
}
void GroupSelectionSystem::Remove(ISelectableEntity*& entity) {
	auto itToD = Singleton->SelectedEntities.cbegin();
	auto it = Singleton->SelectedEntities.begin();
	bool isFound = false;
	for (;it != Singleton->SelectedEntities.cend();++it) {
		if (*it == entity) {
			isFound = true;
			break;
		}
		++itToD;
	}
	if (isFound) {
		Singleton->SelectedEntities.erase_after(itToD);
		entity->SelectionOff();
		Singleton->RemoveSelectableEventHandler.Execute(entity);
	}
}
void GroupSelectionSystem::Clear() {
	for (auto en : Singleton->SelectedEntities) {
		en->SelectionOff();
		Singleton->RemoveSelectableEventHandler.Execute(en);
	}
	Singleton->SelectedEntities.clear();
	Singleton->ClearSelectionEventHandler.Execute();
}
forward_list<ISelectableEntity*>::iterator GroupSelectionSystem::GetEntitiesBegIter() {
	return Singleton->SelectedEntities.begin();
}
forward_list<ISelectableEntity*>::const_iterator GroupSelectionSystem::GetEntitiesEndIter() {
	return Singleton->SelectedEntities.cend();
}
Relation GroupSelectionSystem::GetToPlayertRelOfSelEntities() {
	return Singleton->SelEntsRelationToPl;
}

GroupSelectionSystem* GroupSelectionSystem::Singleton = nullptr;