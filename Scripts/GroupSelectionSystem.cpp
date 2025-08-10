#pragma once

#include <ISelectableEntity.h>
#include <GroupSelectionSystem.h>
#include <iostream>
#include <GameObject.h>
#include <Extensions.h>
#include <DivineCommander.h>

using namespace std;
using namespace KrostganEngine::Debug;
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
		Singleton->SelEntsFraction = frac;
	}
	else {

		bool isEntAlly = rel == Relation::Ally;

		bool canBeNotSingl = isEntAlly || DivineCommander::GetActivity();	//Select more than one entity only if entity is ally or divine commander is active
		if (!canBeNotSingl) {
			return;
		}

		if (isEntAlly) {

			if (Singleton->SelEntsRelationToPl != Relation::Ally) {		//Ally selection is in priority

				Clear();
				Singleton->SelEntsRelationToPl = rel;
				Singleton->SelEntsFraction = frac;
			}
			else if(Singleton->SelEntsFraction!=frac) {		//Can select only entities from one fraction at the same time even when both of them is allies

				return;
			}
		}
		else if(Singleton->SelEntsFraction!=frac) {		//Cannot select entites from different fraction at the same time

			return;
		}
	}


	//else if (rel==Relation::Ally && !DivineCommander::GetActivity()){			//Clear selection group if the group is not ally for player
	//	if (Singleton->SelEntsRelationToPl != Relation::Ally) {		
	//		Clear();
	//		Singleton->SelEntsRelationToPl = rel;
	//	}
	//}
	//else {
	//	return;
	//}
	// Check relation of entity to player for not allowing selection more than one of not ally entity

	Singleton->SelectedEntities.push_front(entity);
	entity->SelectionOn();
	Singleton->AddSelectableEventHandler.Execute(entity);

	GameObject* ref = dynamic_cast<GameObject*>(entity);
	if (ref != nullptr) {
		cout <<ToString(ref->GetGlobalPosition()) << endl;
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

GroupSelectionSystem* GroupSelectionSystem::Singleton = nullptr;