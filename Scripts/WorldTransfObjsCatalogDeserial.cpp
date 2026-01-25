
#include <WorldTransfObjsCatalog.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Extensions.h>
#include <EngineCore.h>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>
#include <WorldObjsCatalogSerConsts.h>

using namespace sf;
using namespace std;
using namespace rapidxml;
using namespace KrostganEngine::Core;

void WorldTransfObjsCatalogDeserial::DeserializeCatalog(const string& serPath) {

	WorldTransfObjsCatalog::Unload();

	char* file = FStreamExts::ReadToEnd(serPath);
	xml_document<>* doc = new xml_document<>();
	doc->parse<0>(file);

	xml_node<>* serObj = doc->first_node()->first_node();
	while (serObj != nullptr) {

		DeserObjForCatalog(*serObj);

		serObj = serObj->next_sibling();
	}

	delete doc;
}

WorldObjectLoadInfo& WorldTransfObjsCatalogDeserial::DeserializeObjInfo(xml_node<>& serObj) {

	char* type = serObj.name();
	WorldObjectLoadInfo* info = nullptr;
	if (type == WorldObjsLoad_Type::OBJECT_TYPE_UNIT) {

		info = new UnitLoadInfo();
	}
	else if (type == WorldObjsLoad_Type::OBJECT_TYPE_HERO) {

		info = new HeroLoadInfo();
	}
	else if (type == WorldObjsLoad_Type::OBJECT_TYPE_WALL) {

		info = new WallLoadInfo();
	}
	else if (type == WorldObjsLoad_Type::OBJECT_TYPE_SPRITE) {

		info = new SpriteRendLoadInfo();
	}
	else if (type == WorldObjsLoad_Type::OBJECT_TYPE_AA_PROJECTILE) {

		info = new AAProjectileLoadInfo();
	}
	else if (type == WorldObjsLoad_Type::OBJECT_TYPE_DECORATION) {

		info = new DecorationLoadInfo();
	}
	else
		throw exception("Cant parse info: uknown type");

	//Load base params of object
	{
		pair< const string, const string>* param = nullptr;
		xml_attribute<>* attr = serObj.first_attribute();
		string paramName;
		string paramValue;
		while (attr != nullptr) {

			paramName = string(attr->name());
			paramValue = string(attr->value());
			param = new pair< const string, const string>(paramName, paramValue);
			info->WriteParam(*param);

			delete param;

			attr = attr->next_attribute();
		}
	}

	//Parse child nodes
	{
		xml_node<>* ch = serObj.first_node();
		while (ch != nullptr) {

			info->WriteParamByNode(*ch);

			ch = ch->next_sibling();
		}

	}

	return *info;
}

void WorldTransfObjsCatalogDeserial::DeserObjForCatalog(xml_node<>& serObj) {

	auto& info = DeserializeObjInfo(serObj);

	WorldTransfObjsCatalog::Add(info);

	//Find sub infos
	{
		xml_node<>* ch = serObj.first_node();
		char* chType = nullptr;
		while (ch != nullptr) {
			
			chType = ch->name();

			if (chType == WorldObjsLoad_XMLChildrenType::SUBINFO) {

				pair<std::byte, WorldObjectLoadInfo*>& parseSub = ParseObjSubInfo(info, *ch);

				WorldTransfObjsCatalog::AddSub(*parseSub.second, parseSub.first);
			}

			ch = ch->next_sibling();
		}
	}
}
pair<std::byte, WorldObjectLoadInfo*>& WorldTransfObjsCatalogDeserial::ParseObjSubInfo(const WorldObjectLoadInfo& base, const xml_node<>& serObj) {

	std::byte subID = ABSENT_SUB_CATALOG_ID;
	//size_t objID = ObjectsCatalog::EMPTY_CATALOG_ID;
	auto& subInfo = base.Clone();
	pair<string, string> parAttr;

	xml_attribute<>* attr = serObj.first_attribute();
	char* attrName = nullptr;
	while (attr != nullptr) {

		attrName = attr->name();
		/*if (attrName == SerializationParDefNames::OBJECT_CATALOG_ID) {

			objID = stol(attr->value());
		}
		else */if (attrName == WorldObjsLoad_ParamDefs::OBJECT_SUB_CATALOG_ID) {

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

	if (subID == ABSENT_SUB_CATALOG_ID /*||
		objID == ObjectsCatalog::EMPTY_CATALOG_ID*/)
		throw exception("Absent definition/s of ID and/or subID");

	return *new pair<std::byte, WorldObjectLoadInfo*>(subID, &subInfo);
}

/// <summary>
/// Return nullptr if cannot parse line
/// </summary>
/// <param name="line"></param>
/// <returns></returns>
const pair<const string, const string>* WorldTransfObjsCatalogDeserial::ParseParamLine(const string& line) {

	size_t index = line.find(PAR_DEF_NAME_END_SYM);
	if (index == string::npos)
		return nullptr;
	string p1 = line.substr(0, index);
	string p2 = line.substr(index + 1, line.size() - index);
	FStreamExts::ClearPath(p1);
	FStreamExts::ClearPath(p2);
	return new pair<const string, const string>(p1, p2);
}