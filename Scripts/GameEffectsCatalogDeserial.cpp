
#include <GameEffectsCatalog.h>
#include <FStreamExts.h>
#include <GameEffectsCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

void GameEffectsCatalogDeserial::DeserializeCatalog(const string& serPath) {

	GameEffectsCatalog::Unload();

	char* file = FStreamExts::ReadToEnd(serPath);
	xml_document<>* doc = new xml_document<>();
	doc->parse<0>(file);

	xml_node<>* serObj = doc->first_node()->first_node();
	while (serObj != nullptr) {

		DeserEffForCatalog(*serObj);

		serObj = serObj->next_sibling();
	}

	delete doc;
}

void	GameEffectsCatalogDeserial::DeserEffForCatalog(xml_node<>& serObj) {

	auto& eff = DeserializeObjInfo(serObj);
	GameEffectsCatalog::Add(eff);
	
	//Find sub infos
	{
		xml_node<>* ch = serObj.first_node();
		char* chType = nullptr;
		while (ch != nullptr) {

			chType = ch->name();

			if (chType == GameEffLoad_XMLChildrenTypes::TYPE_SUBINFO) {

				pair<std::byte, ComposeGameEffectLoadInfo*>& parseSub = ParseObjSubInfo(eff, *ch);

				GameEffectsCatalog::AddSub(*parseSub.second, parseSub.first);
			}

			ch = ch->next_sibling();
		}
	}
}
ComposeGameEffectLoadInfo& GameEffectsCatalogDeserial::DeserializeObjInfo(xml_node<>& serObj) {

	char* type = serObj.name();
	ComposeGameEffectLoadInfo* info = nullptr;
	if (type == GameEffLoad_Types::TYPE_INSTANT) {

		info = new ComposeGameEffectLoadInfo_Instant();
	}
	else if (type == GameEffLoad_Types::TYPE_PERMANENT) {

		info = new ComposeGameEffectLoadInfo_Permanent();
	}
	else if (type == GameEffLoad_Types::TYPE_TEMPORAL) {

		info = new ComposeGameEffectLoadInfo_Temporal();
	}
	else if (type == GameEffLoad_Types::TYPE_PERIODICAL) {

		info = new ComposeGameEffectLoadInfo_Periodical();
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

			if (ch->name() == GameEffLoad_XMLChildrenTypes::TYPE_GENERALGAMEEFF) {

				info->WriteGeneralGameEff(*ch);
			}

			ch = ch->next_sibling();
		}

	}

	return *info;
}
pair<std::byte, ComposeGameEffectLoadInfo*>& GameEffectsCatalogDeserial::ParseObjSubInfo(const ComposeGameEffectLoadInfo& base, const xml_node<>& serObj) {

	std::byte subID = ABSENT_SUB_CATALOG_ID;
	auto& subInfo = base.Clone();
	pair<string, string> parAttr;

	xml_attribute<>* attr = serObj.first_attribute();
	char* attrName = nullptr;
	while (attr != nullptr) {

		attrName = attr->name();
		if (attrName == GameEffLoad_ParamDefNames::EFFECT_SUB_CATALOG_ID) {

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
		subInfo.WriteGeneralGameEff(*childNode);
		childNode = childNode->next_sibling();
	}

	if (subID == ABSENT_SUB_CATALOG_ID)
		throw exception("Absent definition/s of ID and/or subID");

	return *new pair<std::byte, ComposeGameEffectLoadInfo*>(subID, &subInfo);
}