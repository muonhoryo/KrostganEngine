#pragma once

#include <EntitiesControl.h>
#include <iostream>
#include <GameObject.h>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

GroupSelectionSystem::GroupSelectionSystem() {
	Singleton = this;
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
	Singleton->SelectedEntities.push_front(entity);
	entity->SelectionOn();
	GameObject* ref = dynamic_cast<GameObject*>(entity);
	if (ref != nullptr) {
		cout <<VectExts::ToString(ref->GetSpriteGlobalPosition()) << endl;
	}
	else {
		cout << " null " << endl;
	}
}
void GroupSelectionSystem::Remove(ISelectableEntity*& entity) {
	auto itToD = Singleton->SelectedEntities.cbegin();
	auto it = Singleton->SelectedEntities.begin();
	for (;it != Singleton->SelectedEntities.cend();++it) {
		if (*it == entity) {
			break;
		}
		++itToD;
	}
	Singleton->SelectedEntities.erase_after(itToD);
	entity->SelectionOff();
}
void GroupSelectionSystem::Clear() {
	for (auto en : Singleton->SelectedEntities) {
		en->SelectionOff();
	}
	Singleton->SelectedEntities.clear();
}

GroupSelectionSystem* GroupSelectionSystem::Singleton = nullptr;