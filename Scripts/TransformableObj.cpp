
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

//
//
//	getters
//
//

Vector2f			TransformableObj::GetGlobalPosition() const {
	return Owner.getPosition();
}
Vector2f			TransformableObj::GetLocalPosition() const {
	return LocalPosition;
}
Vector2f			TransformableObj::GetGlobalScale() const{
	return Owner.getScale();
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

//
//
//	setters
//
//

void		TransformableObj::SetGlobalPosition	(Vector2f position) {

	Vector2f oldpos = GetGlobalPosition();
	Owner.setPosition(position);
	PrevMovStep = GetGlobalPosition() - oldpos;

	if (Parent==nullptr) {
		LocalPosition = GetGlobalPosition();
	}
	else {
		LocalPosition = GetLocalPositionFromParent();
	}
	SetChildrenPosition();
}
/// <summary>
/// Calculate local position of element from parent's transform
/// </summary>
/// <returns></returns>
Vector2f	TransformableObj::GetLocalPositionFromParent() {
	
	Vector2f origin = Parent->GetOrigin();
	Parent->SetOrigin(DEFAULT_ORIGIN);
	Vector2f result = Parent->GetInverseTransform().transformPoint(GetGlobalPosition());
	Parent->SetOrigin(origin);
	return result;
}
Vector2f	TransformableObj::GetLocalScaleFromParent() {
	Vector2f parScale = Parent->GetGlobalScale();
	Vector2f ownScale = GetGlobalScale();
	ownScale = Vector2f(ownScale.x / parScale.x, ownScale.y / parScale.y);
	return ownScale;
}

void TransformableObj::SetLocalPosition		(Vector2f position) {

	if (Parent == nullptr) {

		SetGlobalPosition(position);
	}
	else {

		Vector2f oldPos = GetGlobalPosition();
		Owner.setPosition(TransformLocalPosToGlobal(position));
		PrevMovStep = GetGlobalPosition() - oldPos;
		LocalPosition = position;
		SetChildrenPosition();
	}
}
Vector2f TransformableObj::TransformLocalPosToGlobal(Vector2f localPos) {

	Vector2f origin = Parent->GetOrigin();
	Parent->SetOrigin(DEFAULT_ORIGIN);
	Vector2f result = Parent->GetTransform().transformPoint(localPos);
	Parent->SetOrigin(origin);
	return result;
}

void TransformableObj::SetGlobalScale	(Vector2f scale) {

	ScaleObject(scale);
	SetChildrenScale();
}
void TransformableObj::ScaleObject		(Vector2f scale) {

	Vector2f glScale = GetGlobalScale();
	Vector2f coef(scale.x / glScale.x, scale.y / glScale.y);
	Owner.setScale(scale);
	LocalScale = Vector2f(coef.x * LocalScale.x, coef.y * LocalScale.y);
}
void TransformableObj::SetLocalScale	(Vector2f scale) {

	LocalScale = scale;
	SetScale_Inherit();
	SetChildrenScale();
}

void TransformableObj::SetChildrenPosition() {
	for (auto ch : ChildObjs) {
		ch->SetPosition_Inherit();
	}
}
void TransformableObj::SetChildrenScale() {
	for (auto ch : ChildObjs) {
		ch->SetScale_Inherit();
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

		Parent->RemoveChild(*this);
		Parent = nullptr;
	}
	if (parent != nullptr) {

		Parent = parent;
		LocalPosition = GetLocalPositionFromParent();
		LocalScale = GetLocalScaleFromParent();
		Parent->AddChild(*this);
	}
	else {
		auto& owner = Owner;
		SetGlobalPosition(pos);
		SetGlobalScale(scale);
	}
	SetChildrenPosition();
	SetChildrenScale();
}
void						TransformableObj::DestroyChildren() {

	vector<TransformableObj*> children = vector<TransformableObj*>(ChildObjs);
	for (auto ch : children) {
		ch->SetParent(nullptr);
		if (ch->GetDesWithParentState())
			delete ch;
	}
	ChildObjs.clear();
}

TransformableObj*			TransformableObj::GetParent() {
	return Parent;
}
TransformableObj const*		TransformableObj::GetParent_c() const {
	return Parent;
}
vector<TransformableObj*>::const_iterator TransformableObj::GetChildrenBegin() const{
	return ChildObjs.cbegin();
}
vector<TransformableObj*>::const_iterator	TransformableObj::GetChildrenEnd() const {
	return ChildObjs.cend();
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
void TransformableObj::SetScale_Inherit() {

	if (Parent == nullptr)
		Owner.setScale(LocalScale);
	else {

		Vector2f parentGlScale = Parent->GetGlobalScale();
		Owner.setScale(LocalScale.x * parentGlScale.x, LocalScale.y * parentGlScale.y);
	}
}

void TransformableObj::AddChild(TransformableObj& child) {

	auto th = this;
	ChildObjs.push_back(&child);
}
void TransformableObj::RemoveChild(TransformableObj& child) {

	if (CollectionsExts::Contains<vector<TransformableObj*>, TransformableObj*>(ChildObjs, &child))
		CollectionsExts::Remove<vector<TransformableObj*>, TransformableObj*>(ChildObjs, &child);
}