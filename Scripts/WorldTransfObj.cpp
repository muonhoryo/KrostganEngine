
#include <WorldTransfObj.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

WorldTransfObj::WorldTransfObj(Transformable& Owner, WorldTransfObj& Parent)
	:HierarchyTrObj(Owner, Parent) {

	ctor_initialize_par();
}

WorldTransfObj::WorldTransfObj(Transformable& Owner)
	:HierarchyTrObj(Owner) {

	ctor_initialize_no_par();
}

//
//
//	getters
//
//

float WorldTransfObj::GetGlobalScale_Sng() const {
	return GetGlobalScale().x;
}
float WorldTransfObj::GetLocalScale_Sng() const {
	return GetLocalScale().x;
}

//
//
//	getters (ITransObj)
//
//

Vector2f			WorldTransfObj::GetLocalPosition() const {
	return LocalPosition;
}
Vector2f			WorldTransfObj::GetLocalScale() const {
	return Vector2f(LocalScale, LocalScale);
}
float				WorldTransfObj::GetLocalRotation() const {
	return LocalRotation;
}
Vector2f			WorldTransfObj::GetPrevMovStep() const {
	return PrevMovStep;
}

//
//
//	setters (ITransObj)
//
//

void WorldTransfObj::SetGlobalPosition	(Vector2f position) {

	Vector2f oldpos = GetGlobalPosition();
	GetOwner_inter().setPosition(position);
	PrevMovStep = GetGlobalPosition() - oldpos;

	if (GetParent() ==nullptr) {
		LocalPosition = GetGlobalPosition();
	}
	else {
		LocalPosition = GetLocalPositionFromParent();
	}
	SetChildrenPosition();
}
void WorldTransfObj::SetLocalPosition		(Vector2f position) {

	if (GetParent() == nullptr) {

		SetGlobalPosition(position);
	}
	else {

		Vector2f oldPos = GetGlobalPosition();
		GetOwner_inter().setPosition(TransformLocalPosToGlobal(position));
		PrevMovStep = GetGlobalPosition() - oldPos;
		LocalPosition = position;
		SetChildrenPosition();
	}
}

void WorldTransfObj::SetGlobalRotation(float rotation) {

	rotation = ClampRotation(rotation);
	GetOwner_inter().setRotation(rotation);
	LocalRotation = rotation;
	auto par = GetParent();
	if (par != nullptr) {
		LocalRotation = ClampRotation(LocalRotation - par->GetGlobalRotation());
	}
	SetChildrenRotation();
}
void WorldTransfObj::SetLocalRotation(float rotation) {

	rotation = ClampRotation(rotation);
	LocalRotation = rotation;
	auto par = GetParent();
	if (par == nullptr) {
		SetGlobalRotation(rotation);
	}
	else {
		GetOwner_inter().setRotation(par->GetGlobalRotation() + LocalRotation);
		SetChildrenRotation();
	}
}

void WorldTransfObj::SetGlobalScale(Vector2f fScale) {

	fScale.x = fScale.y;
	GetOwner_inter().setScale(fScale);
	auto par = GetParent();
	LocalScale = par == nullptr ? fScale.x : fScale.x /= par->GetGlobalScale().x;

	SetChildrenScale();
}
void WorldTransfObj::SetLocalScale(Vector2f scale) {

	scale.y = scale.x;
	LocalScale = scale.x;
	auto par = GetParent();
	if (par == nullptr) {
		GetOwner_inter().setScale(scale);
	}
	else {
		float gScaleValue = par->GetGlobalScale().x * LocalScale;
		Vector2f gScale = Vector2f(gScaleValue, gScaleValue);
		GetOwner_inter().setScale(gScale);
	}
	SetChildrenScale();
}


void WorldTransfObj::SetOrigin(Vector2f origin) {
	GetOwner_inter().setOrigin(origin);
	SetLocalPosition(GetLocalPosition());
}

//
//
// setters (IHierarchyTrObj)
//
//

void WorldTransfObj::SetParent(IHierarchyTrObj* parent) {

	if (GetParent() != nullptr) {

		RemoveOwnerAsChild();
		SetParent_inter(nullptr);
	}
	if (parent != nullptr) {

		SetParent_inter(parent);
		LocalPosition = GetLocalPositionFromParent();
		SetGlobalScale_Sng(LocalScale);
		SetGlobalRotation(GetGlobalRotation());
		AddOwnerAsChild();
	}
	else {
		Vector2f pos = GetGlobalPosition();
		Vector2f scale = GetGlobalScale();
		SetGlobalPosition(pos);
		SetGlobalScale(scale);
	}
	SetChildrenPosition();
	SetChildrenScale();
}


//
//
// Internal funcs
//
//

Vector2f WorldTransfObj::GetLocalPositionFromParent() const{

	Vector2f result = GetParent()->GetInverseTransform().transformPoint(GetGlobalPosition());
	return result;
}
Vector2f WorldTransfObj::TransformLocalPosToGlobal(Vector2f localPos) const {

	Vector2f result = GetParent()->GetTransform().transformPoint(localPos);
	return result;
}

void WorldTransfObj::SetPosition_Inherit() {

	SetLocalPosition(GetLocalPosition());
}
void WorldTransfObj::SetScale_Inherit() {

	SetLocalScale_Sng(LocalScale);
	SetLocalPosition(LocalPosition);
}
void WorldTransfObj::SetRotation_Inherit() {
	SetLocalRotation(LocalRotation);
	SetLocalPosition(LocalPosition);
}