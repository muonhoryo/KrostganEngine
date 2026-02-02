
#include <WorldObjectLoadInfo.h>
#include <LevelManager.h>
#include <WorldObjsCatalogSerConsts.h>
#include <_Extensions.h>

using namespace KrostganEngine::GameObjects;

WorldObjectLoadInfo::WorldObjectLoadInfo(const WorldObjectLoadInfo& copy)
	:ObjectLoadInfo(copy) {

	Name = copy.Name;
	Position = copy.Position;
	Size = copy.Size;
	Rotation = copy.Rotation;
	ChildObjs = vector<LvlObjInstantiationInfo>(copy.ChildObjs);
	WarFog_IsHiden = copy.WarFog_IsHiden;
	LateRender = copy.LateRender;
	WarFog_IsShowed = copy.WarFog_IsShowed;

	Cache = nullptr;
}

WorldTransfObj* WorldObjectLoadInfo::InstantiateObject(LvlObjAdditParams* additParams) const {

	// ???Maybe it should be separate func, cause is used by three instance's in the same form???

	bool isAddParm = additParams != nullptr;
	if (isAddParm) {

		Cache = &Clone();
		for (auto par : additParams->Attrs) {
			Cache->WriteParam(*par);
		}
	}

	auto obj = InstantiateObject_Action(isAddParm ? *Cache : *this);

	if (isAddParm) {

		Cache->InstantiateChildren(*obj);
		delete Cache;
	}
	else {
		InstantiateChildren(*obj);
	}
	LevelManager::InstantiateObjEvHandler.Execute(obj);
	return obj;
}

bool WorldObjectLoadInfo::WriteParam(Attr& param) {

	if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_NAME)) {
		Name = param.second;
	}
	else if (CheckParamName(param, DEF_CATALOG_ID)) {
		CatalogID = stol(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_ROTATION)) {
		Rotation = stof(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_POSITION)) {
		Position = ParseVec2f(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_SIZE)) {
		Size = stof(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_REND_WARFOG_ISHIDEN)) {
		WarFog_IsHiden = FStreamExts::ParseBool(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_REND_WARFOG_ISSHOWED)) {
		WarFog_IsShowed = FStreamExts::ParseBool(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_REND_LATERENDER)) {
		LateRender = FStreamExts::ParseBool(param.second);
	}
	else {
		return false;
	}
	return true;
}
bool WorldObjectLoadInfo::WriteParamByNode(xml_node<>& node) {

	char* nodeName = node.name();

	if (nodeName == WorldObjsLoad_XMLChildrenType::CHILDREN) {

		ChildObjs.clear();
		auto info = LvlObjInstantiationInfo::DeserializeRow(node);
		for (auto in : *info) {
			ChildObjs.push_back(LvlObjInstantiationInfo(*in));
		}
	}
	else
		return false;

	return true;
}

void WorldObjectLoadInfo::InstantiateChildren(WorldTransfObj& parent) const {

	if (RecursionCount >= Engine::GetGlobalConsts().Instantiation_MaxDepthLvl) //Recursion overload check
		throw exception("Instantiating recursion overload");

	//Recursivly instantiate children
	if (ChildObjs.size() != 0) {
		++RecursionCount;

		WorldTransfObj* obj = nullptr;
		for (auto& ch : ChildObjs) {

			obj = ch.InstantiateObj();
			obj->SetParent(&parent);
			obj->SetLocalPosition(DEFAULT_POSITION);
			obj->SetGlobalScale_Sng(parent.GetGlobalScale_Sng() * obj->GetLocalScale_Sng());
			obj->SetLocalRotation(parent.GetGlobalRotation() + obj->GetLocalRotation());
		}
		--RecursionCount;
	}
}