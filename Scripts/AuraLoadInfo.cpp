
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>
#include <GameEffectsCatalog.h>

using namespace KrostganEngine::GameObjects;

AuraLoadInfo::AuraLoadInfo() {

}
AuraLoadInfo::AuraLoadInfo(const AuraLoadInfo& copy)
	:WorldObjectLoadInfo(copy),
		TriggerCollider(&copy.TriggerCollider->Clone()),
		ToTargetRelMask(copy.ToTargetRelMask),
		GameEff_CatalogID(copy.GameEff_CatalogID),
		GameEff_SubCatalogID(copy.GameEff_SubCatalogID),
		AuraFrac(copy.AuraFrac){

}
AuraLoadInfo::~AuraLoadInfo() {
	delete TriggerCollider;
}
WorldObjectLoadInfo& AuraLoadInfo::Clone() const {
	return *new AuraLoadInfo(*this);
}

bool AuraLoadInfo::WriteParam(Attr& param) {

	if (WorldObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, WorldObjsLoad_ParamDefNames::AURA_TOTAR_RELATIONMASK)) {
		ToTargetRelMask = RelationSerialization::DeserializeRelation(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::GAMEEFF_CATALOGID)) {
		GameEff_CatalogID = stoll(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::GAMEEFF_SUBCATALOGID)) {
		GameEff_SubCatalogID = (std::byte)stoi(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::OBJECT_FRACTION)) {
		AuraFrac = *new FractionWrapper(*FractionsSystem::GetFractionByName(param.second));
	}
	else
		return false;

	return true;
}
bool AuraLoadInfo::WriteParamByNode(xml_node<>& node) {

	if (WorldObjectLoadInfo::WriteParamByNode(node))
		return true;

	char* nodeName = node.name();

	if (nodeName == WorldObjsLoad_XMLChildrenType::COLLIDER) {

		if (TriggerCollider != nullptr)
			delete TriggerCollider;
		TriggerCollider = &ColliderDeserializer::DeserializeCollider(node);
	}
	else
		return false;

	return true;
}

WorldTransfObj* AuraLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& gameEff = GameEffectsCatalog::GetObjectInfo(GameEff_CatalogID, GameEff_SubCatalogID).InstantiateGameEff();
	return new Aura
			(TriggerCollider->Clone(), 
			AuraFrac, 
			ToTargetRelMask, 
			*dynamic_cast<ComposeGameEff_Permanent*>(&gameEff));
}