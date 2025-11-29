
#include <UIElement.h>
#include <UserInterfaceManager.h>

using namespace KrostganEngine::UI;

void UIElement::ctor_initialize(Vector2f UISize) {

	Vector2f glPos = GetGlobalPosition();
	this->UISize.x = UISize.x;
	this->UISize.y = UISize.y;
}

UIElement::UIElement(
	Transformable&		Owner,
	UIElement*			Parent,
	const string*		Name,
	Vector2f			UISize,
	byte				RendLayer)
		:HierarchyTrObj(Owner, Parent == nullptr ? UserInterfaceManager::GetRoot() : *Parent),
		ICallbackRec_GraphRen(RendLayer),
		Anchor(Anchor),
		Name(Name==nullptr? "" : *Name)
{
	ctor_initialize(UISize);
	ctor_initialize_par();
}

UIElement::UIElement(
	Transformable&		Owner,
	const string*		Name,
	Vector2f			UISize,
	byte				RendLayer)
		:HierarchyTrObj(Owner),
		ICallbackRec_GraphRen(RendLayer),
		Anchor(Anchor),
		Name(Name==nullptr? "" : *Name)
{
	ctor_initialize(UISize);
	ctor_initialize_no_par();
}

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
float				UIElement::GetLocalRotation() const {
	return GetGlobalRotation();
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

		GetOwner_inter().setPosition(TransformLocalPosToGlobal(position));
		LocalPosition = position;
		SetChildrenPosition();
	}
}
void UIElement::SetGlobalRotation(float rotation) {

	rotation = ClampRotation(rotation);
	GetOwner_inter().setRotation(rotation);
	SetChildrenRotation();
}
void UIElement::SetLocalRotation(float rotation) {
	SetGlobalRotation(rotation);
}
void UIElement::SetGlobalScale(Vector2f scale) {

	Vector2f newUISize = GetLocalUISize();
	GetOwner_inter().setScale(scale);
	LocalScale = GetGlobalScale();
	auto par = GetParent();
	if (par != nullptr) {
		Vector2f parScale = par->GetGlobalScale();
		LocalScale.x /= parScale.x;
		LocalScale.y /= parScale.y;
	}
	SetGlobalUISize(Vector2f(newUISize.x * scale.x, newUISize.y * scale.y));	//UISize is scale with scale of object
	SetChildrenScale();
}
void UIElement::SetLocalScale(Vector2f scale) {

	auto par = GetParent();
	if (par == nullptr) {

		SetGlobalScale(scale);
	}
	else {

		Vector2f newUISize = GetLocalUISize();
		LocalScale = scale;
		Vector2f parScale = par->GetGlobalScale();
		GetOwner_inter().setScale(Vector2f(LocalScale.x * parScale.x, LocalScale.y * parScale.y));
		Vector2f glScale = GetGlobalScale();
		newUISize.x *= glScale.x;
		newUISize.y *= glScale.y;
		SetGlobalUISize(newUISize);
		SetChildrenScale();
	}
}
void UIElement::SetOrigin(Vector2f origin) {
	GetOwner_inter().setOrigin(origin);
	SetLocalPosition(GetLocalPosition());
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
	return Vector2f(UISize.x / glSc.x, UISize.y / glSc.y);
}
const Vector2f& UIElement::GetGlobalUISize() const {
	return UISize;
}
Vector2f UIElement::GetAnchoredOffset() const {
	auto par = dynamic_cast<const UIElement*>(GetParent_c());
	if (par == nullptr)
		return DEFAULT_ANCHOR;
	Vector2f pixAnch = par->GetGlobalUISize();
	pixAnch = Vector2f(pixAnch.x * Anchor.x, pixAnch.y * Anchor.y);
	return pixAnch;
}
Vector2f UIElement::GetAnchoredGlobalPos(Vector2f anchor) const {
	Vector2f pixAnch = GetGlobalUISize();
	pixAnch = Vector2f(pixAnch.x * anchor.x, pixAnch.y * anchor.y);
	return pixAnch + GetGlobalPosition();
}
bool		UIElement::GetResizingUIByInherit() const {
	return ResizeUIByInherits;
}
const string& UIElement::GetName() const {
	return Name;
}
UIElement* UIElement::GetUIElementByName(const string& name) const {
	
	auto it = GetChildrenBegin();
	auto end = GetChildrenCEnd();
	UIElement* el = nullptr;
	for (;it != end;++it) {
		el = dynamic_cast<UIElement*>(*it);
		if (el->GetName() == name)
			return el;
	}
	it = GetChildrenBegin();
	for (;it != end;++it) {
		el = dynamic_cast<UIElement*>(*it);
		el = el->GetUIElementByName(name);
		if (el != nullptr)
			return el;
	}
	return nullptr;
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

void UIElement::SetLocalScaleByUISize(Vector2f localUISize) {

	//Write in localUISize value of localScale
	localUISize = Vector2f(localUISize.x / UISize.x, localUISize.y / UISize.y);
	SetLocalScale(localUISize);
}
void UIElement::SetGlobalScaleByUISize(Vector2f globalUISize) {

	//Write in globalUISize value of globalScale
	globalUISize = Vector2f(globalUISize.x / UISize.x, globalUISize.y / UISize.y);
	SetGlobalScale(globalUISize);
}

void UIElement::SetAnchor(Vector2f anchor) {
	Anchor = anchor;
	SetLocalPosition(GetLocalPosition());
}

void UIElement::SetLocalUISize(Vector2f localSize) {

	Vector2f oldSize = UISize;
	Vector2f glSc = GetGlobalScale();
	UISize.x = localSize.x * glSc.x;
	UISize.y = localSize.y * glSc.y;
	SetChildren_UISize(oldSize);
}
void UIElement::SetGlobalUISize(Vector2f globalSize) {

	Vector2f oldSize = UISize;
	UISize.x = globalSize.x;
	UISize.y = globalSize.y;
	SetChildren_UISize(oldSize);
}
void UIElement::SetUISize_Inherit(Vector2f oldSize) {
	SetLocalPosition(GetLocalPosition());
	if (ResizeUIByInherits) {
		Vector2f coef = dynamic_cast<UIElement*>(GetParent())->GetGlobalUISize();
		coef.x /= oldSize.x;
		coef.y /= oldSize.y;
		Vector2f newSize = GetGlobalUISize();
		newSize.x *= coef.x;
		newSize.y *= coef.y;
		SetGlobalUISize(newSize);
	}
}
void UIElement::SetChildren_UISize(Vector2f oldSize) {
	
	UIElement* ch = nullptr;
	for (auto it = GetChildrenBegin();it != GetChildrenCEnd();++it) {
		ch = dynamic_cast<UIElement*>(*it);
		if (ch != nullptr)
			ch->SetUISize_Inherit(oldSize);
	}
}
void UIElement::SetResizingUIByInherit(bool resizeByInherit) {
	ResizeUIByInherits = resizeByInherit;
}

//
//
//	Internal funcs
//
//


		//Binding transform's center of
		//child element to anchor of parent (not to its origin)
Vector2f	UIElement::GetLocalPositionFromParent() const{

	Vector2f result = GetParent()->GetInverseTransform().transformPoint(GetGlobalPosition());
	result -= GetAnchoredOffset();
	return result;
}
Vector2f	UIElement::GetLocalScaleFromParent() const{

	Vector2f parScale = GetParent()->GetGlobalScale();
	Vector2f ownScale = GetGlobalScale();
	ownScale = Vector2f(ownScale.x / parScale.x, ownScale.y / parScale.y);
	return ownScale;
}
Vector2f	UIElement::TransformLocalPosToGlobal(Vector2f localPos) const{

	Vector2f result = GetParent()->GetTransform().transformPoint(localPos);
	result += GetAnchoredOffset();
	return result;
}

void		UIElement::SetPosition_Inherit() {

	SetLocalPosition(GetLocalPosition());
}
void		UIElement::SetScale_Inherit() {

	if (ResizeUIByInherits) {

		SetLocalScale(LocalScale);
		SetLocalPosition(LocalPosition);
	}
}
void UIElement::SetRotation_Inherit() {
	SetGlobalRotation(GetLocalRotation());
	SetLocalPosition(LocalPosition);
}


