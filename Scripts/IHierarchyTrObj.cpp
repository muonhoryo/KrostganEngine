
#include <IHierarchyTrObj.h>

using namespace KrostganEngine::Core;

void IHierarchyTrObj::AddChild(IHierarchyTrObj& child) {

	auto th = this;
	ChildObjs.push_back(&child);
}
void IHierarchyTrObj::RemoveChild(IHierarchyTrObj& child) {

	if (CollectionsExts::Contains<vector<IHierarchyTrObj*>, IHierarchyTrObj*>(ChildObjs, &child))
		CollectionsExts::Remove<vector<IHierarchyTrObj*>, IHierarchyTrObj*>(ChildObjs, &child);
}
vector<IHierarchyTrObj*>::const_iterator	IHierarchyTrObj::GetChildrenBegin() const {
	return ChildObjs.begin();
}
vector<IHierarchyTrObj*>::const_iterator	IHierarchyTrObj::GetChildrenCEnd() const {
	return ChildObjs.cend();
}
size_t										IHierarchyTrObj::GetChildrenCount() const {
	return ChildObjs.size();
}
bool IHierarchyTrObj::GetDesWithParentState() const {
	return DesWithPar;
}
void	IHierarchyTrObj::DestroyChildren() {

	vector<IHierarchyTrObj*> children = vector<IHierarchyTrObj*>(ChildObjs);
	for (auto ch : children) {
		ch->SetParent(nullptr);
		if (ch->GetDesWithParentState())
			delete ch;
	}
	ChildObjs.clear();
}
void	IHierarchyTrObj::SetDesWithParent(bool desWithPar) {
	DesWithPar = desWithPar;
}

void IHierarchyTrObj::AddOwnerAsChild() {
	GetParent()->AddChild(*this);
}
void IHierarchyTrObj::RemoveOwnerAsChild() {
	GetParent()->RemoveChild(*this);
}
void IHierarchyTrObj::SetChildrenPosition() {

	for (auto ch : ChildObjs) {
		ch->SetPosition_Inherit();
	}
}
void IHierarchyTrObj::SetChildrenScale() {

	for (auto ch : ChildObjs) {
		ch->SetScale_Inherit();
	}
}
void IHierarchyTrObj::SetChildrenRotation() {

	for (auto ch : ChildObjs) {
		ch->SetRotation_Inherit();
	}
}

const vector<IHierarchyTrObj*>&	IHierarchyTrObj::GetChildrenCopy() const {
	return *new vector<IHierarchyTrObj*>(ChildObjs);
}