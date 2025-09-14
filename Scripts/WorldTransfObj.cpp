
#include <WorldTransfObj.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

WorldTransfObj::WorldTransfObj
	(Transformable&		Owner,
	 WorldTransfObj&	Parent,
	 Vector2f			LocalPosition,
	 Vector2f			LocalScale,
	 Vector2f			Origin)
		:LocalScale		(LocalScale),
		HierarchyTrObj(Owner,Parent){

	Vector2f pos = GetGlobalPosition();

	SetOrigin(Origin);
	ctor_initialize_par(LocalPosition,LocalScale);
}

WorldTransfObj::WorldTransfObj
	(Transformable&		Owner,
	WorldTransfObj&	Parent,
	Vector2f			GlobalPosition,
	float				LocalScale,
	Vector2f			Origin)
		:WorldTransfObj(Owner,Parent, GlobalPosition,Vector2f(LocalScale,LocalScale),Origin)
{}

WorldTransfObj::WorldTransfObj
	(Transformable& Owner, 
	 Vector2f		GlobalPosition,
	 Vector2f		GlobalScale,
	 Vector2f		Origin)
		:HierarchyTrObj(Owner),
		LocalScale	(GlobalScale){

	SetOrigin(Origin);
	ctor_initialize_no_par(GlobalPosition, GlobalScale);
}

WorldTransfObj::WorldTransfObj
	(Transformable&		Owner,
	Vector2f			GlobalPosition,
	float				GlobalScale,
	Vector2f			Origin)
		:WorldTransfObj(Owner, GlobalPosition,Vector2f(GlobalScale, GlobalScale),Origin)
{}

//
//
//	getters (ITransObj)
//
//

Vector2f			WorldTransfObj::GetLocalPosition() const {
	return LocalPosition;
}
Vector2f			WorldTransfObj::GetLocalScale() const {
	return LocalScale;
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

void WorldTransfObj::SetGlobalScale	(Vector2f scale) {

	ScaleObject(scale);
	SetChildrenScale();
}
void WorldTransfObj::SetLocalScale	(Vector2f scale) {

	LocalScale = scale;
	SetScale_Inherit();
	SetChildrenScale();
}

void WorldTransfObj::SetOrigin(Vector2f origin) {
	GetOwner_inter().setOrigin(origin);
}

//
//
// setters (IHierarchyTrObj)
//
//

void WorldTransfObj::SetParent(IHierarchyTrObj* parent) {

	Vector2f pos = GetGlobalPosition();
	Vector2f scale = GetGlobalScale();
	if (GetParent() != nullptr) {

		RemoveOwnerAsChild();
		SetParent_inter(nullptr);
	}
	if (parent != nullptr) {

		SetParent_inter(parent);
		LocalPosition = GetLocalPositionFromParent();
		LocalScale = GetLocalScaleFromParent();
		AddOwnerAsChild();
	}
	else {
		auto& owner = GetOwner_inter();
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

Vector2f WorldTransfObj::GetLocalPositionFromParent() {

	Vector2f origin = GetParent()->GetOrigin();
	GetParent()->SetOrigin(DEFAULT_ORIGIN);
	Vector2f result = GetParent()->GetInverseTransform().transformPoint(GetGlobalPosition());
	GetParent()->SetOrigin(origin);
	return result;
}
Vector2f WorldTransfObj::GetLocalScaleFromParent() {

	Vector2f parScale = GetParent()->GetGlobalScale();
	Vector2f ownScale = GetGlobalScale();
	ownScale = Vector2f(ownScale.x / parScale.x, ownScale.y / parScale.y);
	return ownScale;
}
Vector2f WorldTransfObj::TransformLocalPosToGlobal(Vector2f localPos) {

	Vector2f origin = GetParent()->GetOrigin();
	GetParent()->SetOrigin(DEFAULT_ORIGIN);
	Vector2f result = GetParent()->GetTransform().transformPoint(localPos);
	GetParent()->SetOrigin(origin);
	return result;
}

void WorldTransfObj::ScaleObject(Vector2f scale) {

	Vector2f glScale = GetGlobalScale();
	Vector2f coef(scale.x / glScale.x, scale.y / glScale.y);
	GetOwner_inter().setScale(scale);
	LocalScale = Vector2f(coef.x * LocalScale.x, coef.y * LocalScale.y);
}

void WorldTransfObj::SetPosition_Inherit() {

	SetLocalPosition(GetLocalPosition());
}
void WorldTransfObj::SetScale_Inherit() {

	if (GetParent() == nullptr)
		GetOwner_inter().setScale(LocalScale);
	else {

		Vector2f parentGlScale = GetParent()->GetGlobalScale();
		GetOwner_inter().setScale(LocalScale.x * parentGlScale.x, LocalScale.y * parentGlScale.y);
	}
}