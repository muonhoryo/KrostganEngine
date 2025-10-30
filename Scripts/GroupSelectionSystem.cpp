#pragma once

#include <GroupSelectionSystem.h>
#include <iostream>
#include <GameObject.h>
#include <Extensions.h>
#include <DBG_DivineCommander.h>

using namespace std;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

GroupSelectionSystem::GroupSelectionSystem(){
	Singleton = this;
	SelEntsRelationToPl = FractionsSystem::DefaultRel;
	DeathEvSubs = new DeathEventSubscr();
	IDeathModule::DeathEvent_global.Add(*DeathEvSubs);
}
GroupSelectionSystem::~GroupSelectionSystem() {
	Singleton = nullptr;
	IDeathModule::DeathEvent_global.Remove(*DeathEvSubs);
}

GroupSelectionSystem& GroupSelectionSystem::GetInstance() {
	if (GroupSelectionSystem::Singleton == nullptr)
		new GroupSelectionSystem();
	return *GroupSelectionSystem::Singleton;
}

void GroupSelectionSystem::Add(ISelectableEntity& entity) {

	auto& ptr = entity.GetPtr();
	auto& ptr_wr = *new watch_ptr_handler_wr<ISelectableEntity>(ptr);
	delete &ptr;
	if (CollectionsExts::Contains(Singleton->SelectedEntities, &ptr_wr,InstanceEqComparator)) {
		delete &ptr_wr;
		return;
	}

	// Check relation of entity to player for not allowing selection more than one of not ally entity
	ptrdiff_t size = CollectionsExts::Size(Singleton->SelectedEntities);
	IFractionMember* fracEnt = dynamic_cast<IFractionMember*>(&entity);
	Fraction frac = fracEnt == nullptr ? FractionsSystem::DefaultFrac : fracEnt->GetFraction();
	Relation rel = FractionsSystem::GetRelation(frac, Fraction::Player);
	if (size == 0) {
		Singleton->SelEntsRelationToPl = rel;
		Singleton->SelEntsFraction = frac;
	}
	else {

		bool isEntAlly = rel == Relation::Ally;

		bool canBeNotSingl = isEntAlly || DBG_DivineCommander::GetActivity();	//Select more than one entity only if entity is ally or divine commander is active
		if (!canBeNotSingl) {

			delete &ptr_wr;
			return;
		}

		if (isEntAlly) {

			if (Singleton->SelEntsRelationToPl != Relation::Ally) {		//Ally selection is in priority

				Clear();
				Singleton->SelEntsRelationToPl = rel;
				Singleton->SelEntsFraction = frac;
			}
			else if(Singleton->SelEntsFraction!=frac) {		//Can select only entities from one fraction at the same time even when both of them is allies

				delete &ptr_wr;
				return;
			}
		}
		else if(Singleton->SelEntsFraction!=frac) {		//Cannot select entites from different fraction at the same time

			delete &ptr_wr;
			return;
		}
	}

	Add_inter(&ptr_wr);
	entity.SelectionOn();
	Singleton->AddSelectableEventHandler.Execute(entity);
	Singleton->ChangeSelectablesEventHandler.Execute();

	GameObject* ref = dynamic_cast<GameObject*>(&entity);
	if (ref != nullptr) {
		cout <<to_string(ref->GetGlobalPosition()) << endl;
	}
	else {
		cout << " null " << endl;
	}
}
void GroupSelectionSystem::Add_inter(watch_ptr_handler_wr<ISelectableEntity>* entity) {

	CollectionsExts::InsertSorted
		<watch_ptr_handler_wr<ISelectableEntity>*, forward_list<watch_ptr_handler_wr<ISelectableEntity>*> >
		(Singleton->SelectedEntities, entity, InstanceAddComparator);
}

void GroupSelectionSystem::Remove(ISelectableEntity& entity) {
	auto itToD = Singleton->SelectedEntities.before_begin();
	auto it = Singleton->SelectedEntities.begin();
	bool isFound = false;
	for (;it != Singleton->SelectedEntities.cend();++it) {
		if ((*it)->GetPtr_t() == &entity) {
			isFound = true;
			break;
		}
		++itToD;
	}
	if (isFound) {
		delete (*it);
		Singleton->SelectedEntities.erase_after(itToD);
		entity.SelectionOff();
		Singleton->RemoveSelectableEventHandler.Execute(entity);
		Singleton->ChangeSelectablesEventHandler.Execute();
	}
}
void GroupSelectionSystem::Clear() {
	
	ISelectableEntity* ptr = nullptr;
	for (auto& en : Singleton->SelectedEntities) {
		ptr = en->GetPtr_t();
		if(ptr!=nullptr)
			ptr->SelectionOff();
		delete en;
		/*Singleton->RemoveSelectableEventHandler.Execute(ptr);
		Singleton->ChangeSelectablesEventHandler.Execute();*/
	}
	Singleton->SelectedEntities.clear();
	Singleton->ClearSelectionEventHandler.Execute();
	Singleton->ChangeSelectablesEventHandler.Execute();
}

GroupSelectionSystem* GroupSelectionSystem::Singleton = nullptr;