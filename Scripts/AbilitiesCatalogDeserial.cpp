
#include <AbilitiesCatalog.h>
#include <AbilitiesCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

void	AbilitiesCatalogDeserial::DeserializeCatalog(const string& serPath) {

	AbilitiesCatalog::Unload();

	char* file = FStreamExts::ReadToEnd(serPath);
	xml_document<>* doc = new xml_document<>();
	doc->parse<0>(file);

	xml_node<>* serObj = doc->first_node()->first_node();
	while (serObj != nullptr) {

		DeserAbilityForCatalog(*serObj);

		serObj = serObj->next_sibling();
	}

	delete doc;
}

void	AbilitiesCatalogDeserial::DeserAbilityForCatalog(xml_node<>& serObj) {

	auto& ability = DeserializeObjInfo(serObj);
	AbilitiesCatalog::Add(ability);

	//Find sub infos
	{
		xml_node<>* ch = serObj.first_node();
		char* chType = nullptr;
		while (ch != nullptr) {

			chType = ch->name();

			if (chType == AbilitiesLoading_XMLChildrenType::ABILITY_SUBINFO) {

				pair<std::byte, AbilityLoadInfo*>& parseSub = ParseObjSubInfo(ability, *ch);

				AbilitiesCatalog::AddSub(*parseSub.second, parseSub.first);
			}

			ch = ch->next_sibling();
		}
	}
}
AbilityLoadInfo& AbilitiesCatalogDeserial::DeserializeObjInfo(xml_node<>& serObj) {

	char* type = serObj.name();
	AbilityLoadInfo* info = nullptr;

	if (type == AbilitiesLoading_Types::AURA) {
		info = new AbilityLoadInfo_Aura();
	}
	else if (type == AbilitiesLoading_Types::NONTAR_DURABLE) {
		info = new AbilityLoadInfo_NonTar_Durable();
	}
	else if (type == AbilitiesLoading_Types::NONTAR_SETAA) {
		info = new AbilityLoadInfo_NonTar_SetAA();
	}
	else if (type == AbilitiesLoading_Types::NONTAR_TEMPEFF) {
		info = new AbilityLoadInfo_NonTar_TempEff();
	}
	else
		throw exception("Cant parse info: uknown type");
	
	//Load base params of object
	{
		pair< const string, const string>* param = nullptr;
		xml_attribute<>* attr = serObj.first_attribute();
		char* paramName;
		char* paramValue;
		while (attr != nullptr) {

			paramName = attr->name();
			paramValue = attr->value();
			param = new pair< const string, const string>(paramName, paramValue);
			info->WriteParam(*param);

			delete param;

			attr = attr->next_attribute();
		}
	}

	//Load general game effects
	{
		xml_node<>* ch = serObj.first_node();
		while (ch != nullptr) {

			info->WriteParamByNode(*ch);

			ch = ch->next_sibling();
		}

	}

	return *info;
}
pair<std::byte, AbilityLoadInfo*>& AbilitiesCatalogDeserial::ParseObjSubInfo(const AbilityLoadInfo& base, const xml_node<>& serObj) {

	std::byte subID = ABSENT_SUB_CATALOG_ID;
	auto& subInfo = base.Clone();
	pair<string, string> parAttr;

	xml_attribute<>* attr = serObj.first_attribute();
	char* attrName = nullptr;
	while (attr != nullptr) {

		attrName = attr->name();
		if (attrName == ObjectLoadInfo::DEF_SUB_CATALOG_ID) {

			subID = (std::byte)stoi(attr->value());
		}
		else {

			parAttr.first = string(attrName);
			parAttr.second = string(attr->value());
			subInfo.WriteParam(parAttr);
		}

		attr = attr->next_attribute();
	}

	xml_node<>* childNode = serObj.first_node();
	while (childNode != nullptr) {
		subInfo.WriteParamByNode(*childNode);
		childNode = childNode->next_sibling();
	}

	if (subID == ABSENT_SUB_CATALOG_ID)
		throw exception("Absent definition/s of ID and/or subID");

	return *new pair<std::byte, AbilityLoadInfo*>(subID, &subInfo);
}