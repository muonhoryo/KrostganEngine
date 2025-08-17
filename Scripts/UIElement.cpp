
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
	Vector2f			GlobalPosition,
	Vector2f			LocalScale,
	Vector2f			Anchor,
	Vector2f			UISize)
		:ICallbackRec_GraphPostRen(),
		TransformableObj(
			Owner,
			Parent==nullptr?UserInterfaceManager::GetRoot():*Parent,
			GlobalPosition,
			LocalScale),
		Anchor(Anchor)
{
	ctor_initialize(UISize);
	SetLocalScale(LocalScale);
	SetGlobalPosition(GlobalPosition);
}

UIElement::UIElement(
	Transformable&		Owner,
	UIElement*			Parent,
	Vector2f			GlobalPosition,
	float				LocalScale,
	Vector2f			Anchor,
	Vector2f			UISize)
		:UIElement(Owner,Parent,GlobalPosition,Vector2f(LocalScale,LocalScale),Anchor,UISize)
{}

UIElement::UIElement(
	Transformable&		Owner,
	Vector2f			GlobalPosition,
	Vector2f			GlobalScale,
	Vector2f			Anchor,
	Vector2f			UISize)
		:ICallbackRec_GraphPostRen(),
		TransformableObj(Owner,GlobalPosition,GlobalScale),
		Anchor(Anchor)
{
	ctor_initialize(UISize);
	SetGlobalScale(GlobalScale);
	SetGlobalPosition(GlobalPosition);
}

UIElement::UIElement(
	Transformable&		Owner,
	Vector2f			GlobalPosition,
	float				GlobalScale,
	Vector2f			Anchor,
	Vector2f			UISize)
		:UIElement(Owner,GlobalPosition,Vector2f(GlobalScale,GlobalScale),Anchor,UISize)
{}

//
//
//	getters
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
	auto par = dynamic_cast<UIElement const*>(GetParent_c());
	if (par == nullptr)
		return DEFAULT_ANCHOR;
	Vector2f pixAnch =par->GetPixelSize();
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

//
//
//	setters
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
	for (auto it = GetChildrenStart();it != GetChildrenEnd();++it) {
		ch = dynamic_cast<UIElement*>(*it);
		if (ch != nullptr)
			ch->SetUISize_Inherit();
	}
}

//
//
//	overrides
//
//

Vector2f	UIElement::GetLocalPositionFromParent() {
	Vector2f result = TransformableObj::GetLocalPositionFromParent();
	result -= GetAnchoredOffset();
	return result;
}
Vector2f	UIElement::TransformLocalPosToGlobal(Vector2f localPos) {
	Vector2f result = TransformableObj::TransformLocalPosToGlobal(localPos);
	result += GetAnchoredOffset();
	return result;
}

void		UIElement::ScaleObject(Vector2f scale) {

	Vector2f oldLocScale = GetLocalScale();
	TransformableObj::ScaleObject(scale);
	SetGlobalUISize(Vector2f(Borders.width / oldLocScale.x * scale.x,
					Borders.height / oldLocScale.y * scale.y));
}

void		UIElement::SetScale_Inherit() {

	Vector2f oldLocScale = GetGlobalScale();
	TransformableObj::SetScale_Inherit();
	Vector2f coef = GetGlobalScale();
	coef.x = coef.x / oldLocScale.x;
	coef.y = coef.y / oldLocScale.y;
	SetGlobalUISize(Vector2f(Borders.width * coef.x, Borders.height * coef.y));
}


