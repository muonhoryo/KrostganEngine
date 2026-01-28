
#include <LvlLoadingStructs.h>
#include <ObjectsCatalog.h>
#include <WorldObjsCatalog.h>
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>

LvlObjInstantiationInfo::LvlObjInstantiationInfo()
	:CatalogID(EMPTY_CATALOG_ID),
	CatalogSubID(ABSENT_SUB_CATALOG_ID)
{}

void LvlObjInstantiationInfo::Deserialize(const string& serInfo) {

	if (serInfo.length() == 0)
		return;

	AttrsCollectn& attrs = *new AttrsCollectn();
	size_t subInfoIndex = serInfo.find(LVLSER_SUBINFO_SEPARATOR);
	size_t end = serInfo.find(LVLSER_ELEM_PARAMS_DEF);
	string subStr;
	if (end == string::npos) {		//Haven't additional params
		if (subInfoIndex != string::npos) {
			subInfoIndex += LVLSER_SUBINFO_SEPARATOR.length();
			string subs = serInfo.substr(subInfoIndex, serInfo.length() - subInfoIndex);
			CatalogSubID = (std::byte)stoi(subs);
			end = subInfoIndex - LVLSER_SUBINFO_SEPARATOR.length();
		}
		else
			end = serInfo.length();

		subStr = serInfo.substr(0, end);
		CatalogID = stol(subStr);
	}
	else {
		if (subInfoIndex != string::npos &&
			subInfoIndex < end) {		//Index is not part of additional params

			subInfoIndex += LVLSER_SUBINFO_SEPARATOR.length();
			string subs = serInfo.substr(subInfoIndex, end - subInfoIndex - 1);
			CatalogSubID = (std::byte)stoi(subs);
			end = subInfoIndex - LVLSER_SUBINFO_SEPARATOR.length();
		}

		size_t start = 0;
		size_t sepInd = 0;
		subStr = serInfo.substr(0, end);
		CatalogID = stol(subStr);
		start = end + LVLSER_ELEM_PARAMS_DEF.length();
		const pair<const string, const string>* param = nullptr;

		//Read additional params
		while (true) {
			end = serInfo.find(LVLSER_ELEM_PARAMS_DEF, start);
			sepInd = serInfo.find(ObjectsCatalogDeserial::PAR_DEF_NAME_END_SYM, start);
			if (end == string::npos)
				break;
			param = new pair<const string, const string>(serInfo.substr(start, sepInd - start), serInfo.substr(sepInd + 1, serInfo.length() - sepInd));
			attrs.push_back(param);
			start = end + LVLSER_ELEM_PARAMS_DEF.length();
		}
		param = new pair<const string, const string>(serInfo.substr(start, sepInd - start), serInfo.substr(sepInd + 1, serInfo.length() - sepInd));
		attrs.push_back(param);
		if (attrs.size() != 0)
			AdditParams = new LvlObjAdditParams(attrs);
		else
			delete& attrs;
	}
}
void LvlObjInstantiationInfo::Deserialize(const xml_node<>& serInfo) {

	const xml_attribute<>* attr = nullptr;
	char* attrName = nullptr;
	attr = serInfo.first_attribute();
	AttrsCollectn& attrs = *new AttrsCollectn();
	const pair<const string, const string>* param = nullptr;
	string addParamName;
	string addParamValue;

	//Deserialize attributes
	while (attr != nullptr) {

		attrName = attr->name();
		if (attrName == ObjectLoadInfo::DEF_CATALOG_ID) {

			CatalogID = stol(attr->value());
		}
		else if (attrName == ObjectLoadInfo::DEF_SUB_CATALOG_ID) {

			CatalogSubID = (std::byte)stoi(attr->value());
		}
		else {

			addParamName = string(attrName);
			addParamValue = string(attr->value());
			param = new pair<const string, const string>(addParamName, addParamValue);
			attrs.push_back(param);
		}

		attr = attr->next_attribute();
	}


	if (attrs.size() != 0)
		AdditParams = new LvlObjAdditParams(attrs);
	else
		delete& attrs;
}

WorldTransfObj* LvlObjInstantiationInfo::InstantiateObj() const {

	WorldObjectLoadInfo* objInfo = nullptr;
	if (CatalogSubID != ABSENT_SUB_CATALOG_ID)
		objInfo = WorldObjsCatalog::GetSubObjInfo(CatalogID, CatalogSubID);
	else
		objInfo = &WorldObjsCatalog::GetObjectInfo(CatalogID);
	return objInfo->InstantiateObject(AdditParams);
}

vector<LvlObjInstantiationInfo*>* LvlObjInstantiationInfo::DeserializeRow(const string& row) {

	if (row.length() == 0)
		return nullptr;
	vector<LvlObjInstantiationInfo*>& deserRow = *new vector<LvlObjInstantiationInfo*>();
	size_t start = 0;
	size_t end = 0;
	LvlObjInstantiationInfo* celInf = nullptr;
	string elStr;
	while (true) {
		end = row.find(LVLSER_ELEM_ROW_SEPARATOR, start);
		if (end == string::npos) {
			break;
		}

		elStr = row.substr(start, end - start);
		celInf = new LvlObjInstantiationInfo();
		celInf->Deserialize(elStr);
		if (celInf != nullptr)
			deserRow.push_back(celInf);
		start = end + LVLSER_ELEM_ROW_SEPARATOR.length();
	}
	elStr = row.substr(start, row.length() - start);
	celInf = new LvlObjInstantiationInfo();
	celInf->Deserialize(elStr);
	if (celInf->CatalogID != EMPTY_CATALOG_ID)
		deserRow.push_back(celInf);

	if (deserRow.size() > 0)
		return &deserRow;
	else
	{
		delete& deserRow;
		return nullptr;
	}
}

vector<LvlObjInstantiationInfo*>* LvlObjInstantiationInfo::DeserializeRow(const xml_node<>& rootNode) {

	vector<LvlObjInstantiationInfo*>& deserRow = *new vector<LvlObjInstantiationInfo*>();

	LvlObjInstantiationInfo* instInfo = nullptr;
	const xml_node<>* ch = rootNode.first_node();
	while (ch != nullptr) {

		if (ch->name() != WorldObjsLoad_XMLChildrenType::CHILD)
			throw exception("In children field must be only children of object");

		instInfo = new LvlObjInstantiationInfo();

		instInfo->Deserialize(*ch);

		if (instInfo->CatalogID == EMPTY_CATALOG_ID)
			throw exception("Instantiation injo hasn't CatalogID");

		deserRow.push_back(instInfo);

		ch = ch->next_sibling();
	}

	if (deserRow.size() == 0) {

		delete& deserRow;
		return nullptr;
	}
	else
		return &deserRow;
}