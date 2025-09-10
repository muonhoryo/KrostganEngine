
#include <UIElement.h>
#include <UserInterfaceManager.h>

using namespace KrostganEngine::UI;

void UIElement::ctor_initialize(Vector2f UISize) {

	Vector2f glPos = GetGlobalPosition();
	Borders.left = glPos.x;
	Borders.top = glPos.y;
	Borders.width = UISize.x;
	Borders.height = UISize.y;
}

UIElement::UIElement(
	Transformable&		Owner,
	UIElement*			Parent,
	Vector2f			LocalPosition,
	Vector2f			LocalScale,
	Vector2f			Anchor,
	Vector2f			UISize,
	char				RendLayer )
		:ICallbackRec_GraphPostRen(RendLayer),
		HierarchyTrObj(Owner, Parent == nullptr ? UserInterfaceManager::GetRoot() : *Parent),
			Anchor(Anchor)
{
	ctor_initialize(UISize);
	//SetOrigin(Vector2f(0, 0));
	AddOwnerAsChild();
	SetLocalScale(LocalScale);
	SetLocalPosition(LocalPosition);
}

UIElement::UIElement(
	Transformable&		Owner,
	UIElement*			Parent,
	Vector2f			LocalPosition,
	float				LocalScale,
	Vector2f			Anchor,
	Vector2f			UISize,
	char				RendLayer)
		:UIElement(Owner,Parent, LocalPosition,Vector2f(LocalScale,LocalScale),Anchor,UISize,RendLayer)
{}

UIElement::UIElement(
	Transformable&		Owner,
	Vector2f			GlobalPosition,
	Vector2f			GlobalScale,
	Vector2f			Anchor,
	Vector2f			UISize,
	char				RendLayer)
		:ICallbackRec_GraphPostRen(RendLayer),
		HierarchyTrObj(Owner),
		Anchor(Anchor)
{
	ctor_initialize(UISize);
	//SetOrigin(Vector2f(0, 0));
	SetGlobalScale(GlobalScale);
	SetGlobalPosition(GlobalPosition);
}

UIElement::UIElement(
	Transformable&		Owner,
	Vector2f			GlobalPosition,
	float				GlobalScale,
	Vector2f			Anchor,
	Vector2f			UISize,
	char				RendLayer)
		:UIElement(Owner,GlobalPosition,Vector2f(GlobalScale,GlobalScale),Anchor,UISize,RendLayer)
{}

//
//
//	getters (TransformableObj)
//
//

Vector2f			UIElement::GetLocalPosition() const {
	return LocalPosition;
}
Vector2f			UIElement::GetLocalScale() const {
	return LocalScale;
}

//
//
//	setters (TransformableObj)
//
//

void UIElement::SetGlobalPosition(Vector2f position) {

	Vector2f oldpos = GetGlobalPosition();
	GetOwner_inter().setPosition(position);

	if (GetParent() == nullptr) {
		LocalPosition = GetGlobalPosition();
	}
	else {
		LocalPosition = GetLocalPositionFromParent();
	}
	SetChildrenPosition();
}
void UIElement::SetLocalPosition(Vector2f position) {

	if (GetParent() == nullptr) {

		SetGlobalPosition(position);
	}
	else {

		Vector2f oldPos = GetGlobalPosition();
		GetOwner_inter().setPosition(TransformLocalPosToGlobal(position));
		LocalPosition = position;
		SetChildrenPosition();
	}
}
void UIElement::SetGlobalScale(Vector2f scale) {

	ScaleElement(scale);
	SetChildrenScale();
}
void UIElement::SetLocalScale(Vector2f scale) {

	LocalScale = scale;
	SetScale_Inherit();
	SetChildrenScale();
}
void UIElement::SetOrigin(Vector2f origin) {
	GetOwner_inter().setOrigin(origin);
}

//
//
// setters (HierarchyTrObj)
//
//

void UIElement::SetParent(IHierarchyTrObj* parent) {

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
// getters (UI)
//
//

Vector2f UIElement::GetAnchor() const {
	return Anchor;
}
Vector2f UIElement::GetLocalUISize() const {
	Vector2f glSc = GetGlobalScale();
	return Vector2f(Borders.width / glSc.x, Borders.height / glSc.y);
}
Vector2f UIElement::GetGlobalUISize() const {
	return Vector2f(Borders.width, Borders.height);
}
Vector2f UIElement::GetPixelSize() const {
	Vector2f parScale = GetGlobalScale();
	return Vector2f(Borders.width * parScale.x, Borders.height * parScale.y);
}
Vector2f UIElement::GetAnchoredOffset() const {
	auto par = dynamic_cast<const UIElement*>(GetParent_c());
	if (par == nullptr)
		return DEFAULT_ANCHOR;
	Vector2f pixAnch = par->GetPixelSize();
	pixAnch = Vector2f(pixAnch.x * Anchor.x, pixAnch.y * Anchor.y);
	return pixAnch;
}
Vector2f UIElement::GetAnchoredGlobalPos(Vector2f anchor) const {
	Vector2f pixAnch = GetPixelSize();
	pixAnch = Vector2f(pixAnch.x * anchor.x, pixAnch.y * anchor.y);
	return pixAnch + GetGlobalPosition();
}
const Rect<float>& UIElement::GetBorders() const {
	return Borders;
}

bool		UIElement::GetActivity() const {
	return GetSelfActivity() && GetInheritActivity();
}
bool		UIElement::GetInheritActivity() const {
	auto par = dynamic_cast<const UIElement*>(GetParent_c());
	return par == nullptr ? true : par->GetActivity();
}
bool		UIElement::GetSelfActivity() const {
	return IsActive;
}

//
//
//	setters (UI)
//
//

void UIElement::SetLocalScaleByUISize(Vector2f uiSize) {

	uiSize = Vector2f(uiSize.x / Borders.width, uiSize.y / Borders.height);
	SetLocalScale(uiSize);
}
void UIElement::SetGlobalScaleByUISize(Vector2f uiSize) {

	uiSize = Vector2f(uiSize.x / Borders.width, uiSize.y / Borders.height);
	SetGlobalScale(uiSize);
}

void UIElement::SetAnchor(Vector2f anchor) {
	Anchor = anchor;
	SetLocalPosition(GetLocalPosition());
}

void UIElement::SetLocalUISize(Vector2f localSize) {

	Vector2f glSc = GetGlobalScale();
	Borders.width = localSize.x * glSc.x;
	Borders.height = localSize.y * glSc.y;
	SetChildren_UISize();
}
void UIElement::SetGlobalUISize(Vector2f globalSize) {

	Borders.width = globalSize.x;
	Borders.height = globalSize.y;
	SetChildren_UISize();
}
void UIElement::SetUISize_Inherit() {
	SetLocalPosition(GetLocalPosition());
}
void UIElement::SetChildren_UISize() {
	
	UIElement* ch = nullptr;
	for (auto it = GetChildrenBegin();it != GetChildrenCEnd();++it) {
		ch = dynamic_cast<UIElement*>(*it);
		if (ch != nullptr)
			ch->SetUISize_Inherit();
	}
}

//
//
//	Internal funcs
//
//


		//Binding transform's center of
		//child element to anchor of parent (not to its origin)
Vector2f	UIElement::GetLocalPositionFromParent() {

	Vector2f origin = GetParent()->GetOrigin();
	GetParent()->SetOrigin(DEFAULT_ORIGIN);
	Vector2f result = GetParent()->GetInverseTransform().transformPoint(GetGlobalPosition());
	result -= GetAnchoredOffset();
	GetParent()->SetOrigin(origin);
	return result;
}
Vector2f	UIElement::GetLocalScaleFromParent() {

	Vector2f parScale = GetParent()->GetGlobalScale();
	Vector2f ownScale = GetGlobalScale();
	ownScale = Vector2f(ownScale.x / parScale.x, ownScale.y / parScale.y);
	return ownScale;
}
Vector2f	UIElement::TransformLocalPosToGlobal(Vector2f localPos) {

	Vector2f origin = GetParent()->GetOrigin();
	GetParent()->SetOrigin(DEFAULT_ORIGIN);
	Vector2f result = GetParent()->GetTransform().transformPoint(localPos);
	result += GetAnchoredOffset();
	GetParent()->SetOrigin(origin);
	return result;
}

void		UIElement::ScaleElement(Vector2f scale) {

	Vector2f oldLocScale = GetLocalScale();
	Vector2f glScale = GetGlobalScale();
	Vector2f coef(scale.x / glScale.x, scale.y / glScale.y);
	GetOwner_inter().setScale(scale);
	LocalScale = Vector2f(coef.x * LocalScale.x, coef.y * LocalScale.y);
	SetGlobalUISize(Vector2f(Borders.width / oldLocScale.x * scale.x,
					Borders.height / oldLocScale.y * scale.y));
}

void		UIElement::SetPosition_Inherit() {

	SetLocalPosition(GetLocalPosition());
}
void		UIElement::SetScale_Inherit() {

	Vector2f oldLocScale = GetGlobalScale();
	if (GetParent() == nullptr)
		GetOwner_inter().setScale(LocalScale);
	else {

		Vector2f parentGlScale = GetParent()->GetGlobalScale();
		GetOwner_inter().setScale(LocalScale.x * parentGlScale.x, LocalScale.y * parentGlScale.y);
	}
	Vector2f coef = GetGlobalScale();
	coef.x = coef.x / oldLocScale.x;
	coef.y = coef.y / oldLocScale.y;
	SetGlobalUISize(Vector2f(Borders.width * coef.x, Borders.height * coef.y));
}


