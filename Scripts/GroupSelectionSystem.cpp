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
	if (Singleton != nullptr)
		throw exception("Trying to recreate GroupSelectionSystem");

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

void GroupSelectionSystem::RemoveNullable() {
	auto it = GetSelectedEnts_Begin();
	auto end = GetSelectedEnts_End();
	auto prevIt = Singleton->SelectedEntities.before_begin();
	while (it != end) {

		if ((*it)->GetPtr_t() == nullptr) {

			Singleton->SelectedEntities.erase_after(prevIt);
			it = prevIt;
			++it;
		}
		else {
			++it;
			++prevIt;
		}
	}
}
GroupSelectionSystem::SelectedEntsPredicate GroupSelectionSystem::GetPredForCurrChoosenGroup() {
	return SelectedEntsPredicate(Singleton->ChoosenEntitesCatalInfo);
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
	Fraction frac = fracEnt == nullptr ? FractionsSystem::DEFAULT_FRAC : fracEnt->GetFraction();
	Relation rel = FractionsSystem::GetRelation(frac, Fraction::Player);
	auto catObj = dynamic_cast<CatalogObject*>(&entity);
	if (size == 0) {
		Singleton->SelEntsRelationToPl = rel;
		Singleton->SelEntsFraction = frac;
		if (catObj == nullptr) {
			Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;
		}
		else {
			Singleton->ChoosenEntitesCatalInfo.first = catObj->GetCatalogID();
			Singleton->ChoosenEntitesCatalInfo.second = catObj->GetSubcatalogID();
		}
		Singleton->ChangeChoosenGroupEvHan.Execute(Singleton->ChoosenEntitesCatalInfo);
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
	auto predicate = GetPredForCurrChoosenGroup();
	if (predicate.Condition(&ptr_wr)) {
		Singleton->AddEntToChoosenEvHan.Execute(entity);
		Singleton->ChangeChoosenEntsEvHan.Execute();
	}
	Singleton->AddSelectableEventHandler.Execute(entity);
	Singleton->ChangeSelectablesEventHandler.Execute();
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

		auto predicate = GetPredForCurrChoosenGroup();
		bool wasChoosen = predicate.Condition(*it);
		delete (*it);
		Singleton->SelectedEntities.erase_after(itToD);
		entity.SelectionOff();
		if (wasChoosen) {

			auto chooseIt = GetChoosenEntities_Begin();
			
			//Old choosen group is empty
			if (chooseIt == GetSelectedEnts_End()) {
				if (GetSelectionCount() == 0) {

					Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;
				}
				else {

					auto first = (*GetSelectedEnts_Begin())->GetPtr_t();
					auto parfirst = dynamic_cast<CatalogObject*>(first);
					if (parfirst == nullptr) {

						Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;
					}
					else {
						Singleton->ChoosenEntitesCatalInfo.first = parfirst->GetCatalogID();
						Singleton->ChoosenEntitesCatalInfo.second = parfirst->GetSubcatalogID();
					}
				}

				Singleton->ChangeChoosenGroupEvHan.Execute(Singleton->ChoosenEntitesCatalInfo);
			}
			
			Singleton->RemoveEntFromChoosenEvHan.Execute(entity);
			Singleton->ChangeChoosenEntsEvHan.Execute();
		}

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
	}
	Singleton->SelectedEntities.clear();
	Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;

	Singleton->ChangeChoosenGroupEvHan.Execute(Singleton->ChoosenEntitesCatalInfo);
	Singleton->ChangeChoosenEntsEvHan.Execute();
	Singleton->ClearSelectionEventHandler.Execute();
	Singleton->ChangeSelectablesEventHandler.Execute();
}

forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::iterator GroupSelectionSystem::GetChoosenEntities_Begin(){

	RemoveNullable();
	auto it = GetSelectedEnts_Begin();
	auto end = GetSelectedEnts_End();
	auto predicate = GetPredForCurrChoosenGroup();
	for (;it != end;++it) {
		if (predicate.Condition(*it)) {
			return it;
		}
	}

	return it;
}
forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator GroupSelectionSystem::GetChoosenEntities_End() {

	RemoveNullable();
	auto it = GetSelectedEnts_Begin();
	auto end = GetSelectedEnts_End();
	if (it == end)
		return end;
	auto predicate = GetPredForCurrChoosenGroup();
	for (;it != end;++it) {
		if (predicate.Condition(*it)) {
			break;
		}
	}
	forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator postIt = it;
	++postIt;
	while (postIt != end) {

		if (!predicate.Condition(*postIt)) {

			break;
		}
		++postIt;
	}
	return postIt;
}
pair<size_t, std::byte>	GroupSelectionSystem::ChoiseNextEntsGroup() {

	RemoveNullable();
	size_t selectionCount = GetSelectionCount();
	
	//Check if selection is empty or selected only one group
	if (selectionCount == 0 ||
		selectionCount == GetChoosenGroupCount()) {

		return Singleton->ChoosenEntitesCatalInfo;
	}

	auto it = GetChoosenEntities_End();
	auto end = GetSelectedEnts_End();
	if (it == end) {
		it = GetSelectedEnts_Begin();
	}

	auto catObj = dynamic_cast<CatalogObject*>((*it)->GetPtr_t());
	if (catObj == nullptr) {

		Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;
	}
	else {

		Singleton->ChoosenEntitesCatalInfo = pair<size_t, std::byte>(catObj->GetCatalogID(), catObj->GetSubcatalogID());
	}
	
	Singleton->ChangeChoosenGroupEvHan.Execute(Singleton->ChoosenEntitesCatalInfo);
	return Singleton->ChoosenEntitesCatalInfo;
}
pair<size_t, std::byte>	GroupSelectionSystem::ChoisePrevEntsGroup() {

	RemoveNullable();
	size_t selectionCount = GetSelectionCount();

	//Check if selection is empty or selected only one group
	if (selectionCount == 0 ||
		selectionCount == GetChoosenGroupCount()) {

		return Singleton->ChoosenEntitesCatalInfo;
	}

	auto it = GetSelectedEnts_Begin();
	auto end = GetSelectedEnts_End();

	SelectedEntsPredicate predicate = SelectedEntsPredicate(Singleton->ChoosenEntitesCatalInfo);

	//Choosen objects are first in list
	if (predicate.Condition(*it)) {

		forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::iterator  prevIt = it;
		++it;
		while (it != end) {
			++it;
			++prevIt;
		}
		
		auto catObj = dynamic_cast<CatalogObject*>((*it)->GetPtr_t());
		if (catObj == nullptr) {

			Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;
		}
		else {

			Singleton->ChoosenEntitesCatalInfo.first = catObj->GetCatalogID();
			Singleton->ChoosenEntitesCatalInfo.second = catObj->GetSubcatalogID();
		}
	}
	//Choosen objects are next first in list
	else {

		forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::iterator  prevIt = it;
		++it;
		while (!predicate.Condition(*it)) {
			++prevIt;
			++it;
		}

		auto catObj = dynamic_cast<CatalogObject*>((*prevIt)->GetPtr_t());
		if (catObj == nullptr) {

			Singleton->ChoosenEntitesCatalInfo = ZERO_CHOISE;
		}
		else {

			Singleton->ChoosenEntitesCatalInfo.first = catObj->GetCatalogID();
			Singleton->ChoosenEntitesCatalInfo.second = catObj->GetSubcatalogID();
		}
	}

	Singleton->ChangeChoosenGroupEvHan.Execute(Singleton->ChoosenEntitesCatalInfo);
	return Singleton->ChoosenEntitesCatalInfo;
}