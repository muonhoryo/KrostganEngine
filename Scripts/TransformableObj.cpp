
#include <TransformableObj.h>
#include <CollectionsExts.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

TransformableObj::~TransformableObj() {

	for (auto ch : ChildObjs) {
		if (ch->DesWithPar)
			delete ch;
		else
			ch->SetParent(nullptr);
	}
	if (Parent != nullptr)
		Parent->RemoveChild(*this);
}
TransformableObj::TransformableObj
	(Transformable&		Owner,
	 TransformableObj&	Parent,
	 Vector2f			GlobalPosition, 
	 Vector2f			LocalScale,
	 Vector2f			Origin)
		:Owner			(Owner),
		LocalScale		(LocalScale),
		//GlobalScale		(LocalScale),
		Parent			(&Parent){

	Vector2f pos = GetGlobalPosition();

	SetOrigin(Origin);
	/*SetGlobalPosition(LocalPosition);
	SetGlobalScale(LocalScale);*/
	Parent.AddChild(*this);
	SetLocalScale(LocalScale);
	SetGlobalPosition(GlobalPosition);

	pos = GetGlobalPosition();
}

TransformableObj::TransformableObj
	(Transformable&		Owner,
	TransformableObj&	Parent,
	Vector2f			GlobalPosition,
	float				LocalScale,
	Vector2f			Origin)
		:TransformableObj(Owner,Parent, GlobalPosition,Vector2f(LocalScale,LocalScale),Origin)
{}

TransformableObj::TransformableObj
	(Transformable& Owner, 
	 Vector2f		GlobalPosition,
	 Vector2f		GlobalScale,
	 Vector2f		Origin)
		:Owner		(Owner),
		//GlobalScale (GlobalScale)
		LocalScale	(GlobalScale){

	SetOrigin(Origin);
	SetGlobalScale(GlobalScale);
	SetGlobalPosition(GlobalPosition);
}

TransformableObj::TransformableObj
	(Transformable&		Owner,
	Vector2f			GlobalPosition,
	float				GlobalScale,
	Vector2f			Origin)
		:TransformableObj(Owner, GlobalPosition,Vector2f(GlobalScale, GlobalScale),Origin)
{}

Vector2f			TransformableObj::GetGlobalPosition() const {
	return Owner.getPosition();
}
Vector2f			TransformableObj::GetLocalPosition() const {
	return LocalPosition;
	/*if (Parent == nullptr) {

		return Owner.getPosition();
	}
	else {

		return Parent->Owner.getInverseTransform().transformPoint(GetGlobalPosition());
	}*/
}
Vector2f			TransformableObj::GetGlobalScale() const{
	return Owner.getScale();
	//return GlobalScale;
}
Vector2f			TransformableObj::GetLocalScale() const {
	return LocalScale;
}
Vector2f			TransformableObj::GetOrigin() const {
	return Owner.getOrigin();
}
Vector2f			TransformableObj::GetPrevMovStep() const {
	return PrevMovStep;
}
const Transform&	TransformableObj::GetTransform() const{
	return Owner.getTransform();
}
const Transform& TransformableObj::GetInverseTransform() const {
	return Owner.getInverseTransform();
}

void TransformableObj::SetGlobalPosition	(Vector2f position) {
	SetGlobalPosition_Inter(position, Parent == nullptr);
}
void TransformableObj::SetLocalPosition		(Vector2f position) {

	if (Parent == nullptr) {

		SetGlobalPosition_Inter(position,false);
		LocalPosition = position;
	}
	else {

		Vector2f oldpos = GetGlobalPosition();
		Vector2f origin = Parent->GetOrigin();
		Parent->SetOrigin(Vector2f(0,0));
		Owner.setPosition(Parent->GetTransform().transformPoint(position));
		PrevMovStep = GetGlobalPosition() - oldpos;
		LocalPosition = position;
		Parent->SetOrigin(origin);
		for (auto ch : ChildObjs) {
			ch->SetPosition_Inherit();
		}
	}
}
Vector2f TransformableObj::GetLocalPosition_Inter() {
	return Parent->GetInverseTransform().transformPoint(GetGlobalPosition());
}
void TransformableObj::SetGlobalPosition_Inter(Vector2f position, bool isFree) {

	Vector2f oldpos = GetGlobalPosition();
	Owner.setPosition(position);
	PrevMovStep = GetGlobalPosition() - oldpos;

	if (isFree) {
		LocalPosition = GetGlobalPosition();
	}
	else {
		Vector2f origin = Parent->GetOrigin();
		Parent->SetOrigin(Vector2f(0,0));
		LocalPosition = GetLocalPosition_Inter();
		Parent->SetOrigin(Vector2f(0, 0));
	}

	for (auto ch : ChildObjs) {
		ch->SetPosition_Inherit();
	}
}

void TransformableObj::SetGlobalScale		(Vector2f scale) {

	Vector2f glScale = GetGlobalScale();
	Vector2f coef (scale.x / glScale.x,scale.y/ glScale.y);
	Owner.setScale(scale);
	LocalScale= Vector2f(coef.x * LocalScale.x,coef.y * LocalScale.y);
	//GlobalScale = scale;
	for (auto ch : ChildObjs) {
		ch->SetScale_Inherit(GetGlobalScale());
	}
}
void TransformableObj::SetLocalScale		(Vector2f scale) {

	LocalScale = scale;
	SetScale_Inherit(Parent == nullptr ? DEFAULT_SCALE : Parent->GetGlobalScale());
	for (auto ch : ChildObjs) {
		ch->SetScale_Inherit(GetGlobalScale());
	}
}

void TransformableObj::SetOrigin(Vector2f origin) {
	Owner.setOrigin(origin);
}

/// <summary>
/// Move globaly
/// </summary>
/// <param name="movValue"></param>
void TransformableObj::Move_Global	(Vector2f movValue) {
	Vector2f nextPos = GetGlobalPosition() + movValue;
	SetGlobalPosition(nextPos);
}
void TransformableObj::Move_Local	(Vector2f moveValue) {
	Vector2f nextPos = GetLocalPosition() + moveValue;
	SetLocalPosition(nextPos);
}

void				TransformableObj::SetParent(TransformableObj* parent) {

	Vector2f pos = GetGlobalPosition();
	Vector2f scale = GetGlobalScale();
	if (Parent != nullptr) {

		SetScale_Inherit(DEFAULT_SCALE);
		Parent->RemoveChild(*this);
		Parent = nullptr;
	}
	if (parent != nullptr) {

		Parent = parent;
		SetPosition_Inherit();
		SetScale_Inherit(parent->GetGlobalScale());
		Parent->AddChild(*this);
	}
	else {
		SetGlobalPosition(pos);
		SetGlobalScale(scale);
	}
	for (auto ch : ChildObjs) {
		ch->SetPosition_Inherit();
	}
	for (auto ch : ChildObjs) {
		ch->SetScale_Inherit(GetGlobalScale());
	}
}
TransformableObj&	TransformableObj::GetParent() {
	return *Parent;
}

void TransformableObj::SetDesWithParent(bool desWithPar) {
	DesWithPar = desWithPar;
}
bool TransformableObj::GetDesWithParentState() const {
	return DesWithPar;
}

void TransformableObj::SetPosition_Inherit() {

	SetLocalPosition(GetLocalPosition());
}
void TransformableObj::SetScale_Inherit(Vector2f parentGlScale) {

	Owner.setScale(LocalScale.x * parentGlScale.x, LocalScale.y * parentGlScale.y);
	//GlobalScale = Vector2f(LocalScale.x * parentGlScale.x, LocalScale.y * parentGlScale.y);
	//Owner.setScale(GlobalScale);
}

void TransformableObj::AddChild(TransformableObj& child) {

	ChildObjs.push_back(&child);
}
void TransformableObj::RemoveChild(TransformableObj& child) {

	if(CollectionsExts::Contains<vector<TransformableObj*>, TransformableObj*>(ChildObjs,&child))
		CollectionsExts::Remove<vector<TransformableObj*>, TransformableObj*>(ChildObjs, &child);
}