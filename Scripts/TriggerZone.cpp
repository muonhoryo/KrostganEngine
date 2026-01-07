
#include <TriggerZone.h>
#include <CollectionsExts.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

TriggerZone::TriggerZone(Transformable& Owner, WorldTransfObj& Parent)
	:WorldTransfObj(Owner,Parent){

}
TriggerZone::TriggerZone(Transformable& Owner) 
	:WorldTransfObj(Owner){

}
TriggerZone::~TriggerZone() {
	for (auto ptr : EnteredObjects) {
		OnTriggerExit(*ptr);
		delete ptr;
	}
}

forward_list<watch_ptr_handler_wr<IPhysicalObject>*>::const_iterator TriggerZone::GetEnteredObjs_BeforeBegin() const {
	return EnteredObjects.before_begin();
}
forward_list<watch_ptr_handler_wr<IPhysicalObject>*>::const_iterator TriggerZone::GetEnteredObjs_Begin() const {
	return EnteredObjects.begin();
}
forward_list<watch_ptr_handler_wr<IPhysicalObject>*>::const_iterator TriggerZone::GetEnteredObjs_End() const {
	return EnteredObjects.end();
}

void TriggerZone::Update(CallbackRecArgs_Upd args) {

	Update_DeleteNull();

	auto inputObjs = OverlapAll();
	Update_DeleteExited(inputObjs);
	Update_AddEnteredObjs(inputObjs);
}
void TriggerZone::RecalculateEnteredObjs() {

	for (auto tar : EnteredObjects) {
		OnTriggerExit(*tar);
		delete tar;
	}
	EnteredObjects.clear();
	Update(CallbackRecArgs_Upd(vector<Event>(), Engine::GetFrameDeltaTime()));
}

void TriggerZone::Update_DeleteNull() {
	
	auto befIt = EnteredObjects.before_begin();
	auto it = EnteredObjects.begin();
	auto end = EnteredObjects.end();
	watch_ptr_handler_wr<IPhysicalObject>* ptr = nullptr;
	while (it != end) {

		ptr = *it;
		if (ptr->GetPtr_t() == nullptr) {

			OnTriggerExit(*ptr);
			delete ptr;
			EnteredObjects.erase_after(befIt);
			it = befIt;
		}

		++it;
		++befIt;
	}
}
void TriggerZone::Update_DeleteExited(const vector<IPhysicalObject*>& inputObjs) {

	auto befIt = EnteredObjects.before_begin();
	auto it = EnteredObjects.begin();
	auto end = EnteredObjects.end();
	watch_ptr_handler_wr<IPhysicalObject>* ptr = nullptr;
	while (it != end) {

		ptr = *it;
		if (!CollectionsExts::Contains(inputObjs, ptr->GetPtr_t())) {

			OnTriggerExit(*ptr);
			delete ptr;
			EnteredObjects.erase_after(befIt);
			it = befIt;
		}

		++it;
		++befIt;
	}
}
void TriggerZone::Update_AddEnteredObjs(const vector<IPhysicalObject*>& inputObjs) {

	auto it = inputObjs.begin();
	auto end = inputObjs.end();
	IPhysicalObject* obj = nullptr;
	watch_ptr_handler_wr<IPhysicalObject>* ptr = nullptr;
	while (it != end) {

		obj = *it;
		ptr = new watch_ptr_handler_wr<IPhysicalObject>(obj->GetPtr());

		if (CollectionsExts::Contains(EnteredObjects, ptr, InstanceEqComparator)) {

			OnTriggerStay(*obj);
		}
		else if (EnterTriggerCondition(*obj)) {

			EnteredObjects.push_front(ptr);
			OnTriggerEnter(*obj);
		}

		++it;
	}
}