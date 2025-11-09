
#include <ObjectsCatalog.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Extensions.h>
#include <EngineCore.h>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>

using namespace KrostganEngine::Core;

void ObjsCatalogDeserial::DeserializeCatalog(string serPath) {

	string line;
	ifstream st(serPath);
	if (st.bad() == true ||
		st.fail() == true)
		throw exception("Cannot open level file");

	ObjectsCatalog::Unload();

	vector<string>& params = *new vector<string>();
	pair<size_t, _ObjSubsPairType>* subinfo = nullptr;
	if (st.is_open()) {
		while (getline(st, line)) {

			if (line.find(OBJECTS_SEP_LINE) != string::npos) {

				if (params[0].find(SerializationParDefNames::OBJECT_TYPE) != string::npos) {

					ObjectsCatalog::Add(&ParseObjInfo(params));
				}
				else if(params[0].find(SerializationParDefNames::CATALOG_SUB_INFO_ID)!=string::npos){
					
					subinfo = &ParseObjSubinfo(params);
					ObjectsCatalog::AddSub(subinfo->first,subinfo->second.first,*subinfo->second.second);
					delete subinfo;
				}
				params.clear();
			}
			else {

				if(line.size()>1)
					params.push_back(line);
			}
		}
	}
	st.close();
	size_t size = params.size();
	if (size > 1 ||
		size == 1 && params[0].size() > 1) {

		if (params[0].find(SerializationParDefNames::OBJECT_TYPE) != string::npos) {

			ObjectsCatalog::Add(&ParseObjInfo(params));
		}
		else if (params[0].find(SerializationParDefNames::CATALOG_SUB_INFO_ID) != string::npos) {

			subinfo = &ParseObjSubinfo(params);
			ObjectsCatalog::AddSub(subinfo->first, subinfo->second.first, *subinfo->second.second);
			delete subinfo;
		}
	}
	params.clear();
	ObjectsCatalog::GetObjectInfo(0);
	delete& params;
}

WorldObjectLoadInfo& ObjsCatalogDeserial::ParseObjInfo(const vector<string>& params) {

	WorldObjectLoadInfo* info = nullptr;
	const pair<const string, const string>* parParam = nullptr;
	parParam = &ParseParamLine(params[0]);

	if (parParam->first.find(SerializationParDefNames::OBJECT_TYPE) != string::npos)
	{
		if (parParam->second.find(SerializationObjectsTypes::OBJECT_TYPE_UNIT) != string::npos) {

			info = new UnitLoadInfo();
		}
		else if (parParam->second.find(SerializationObjectsTypes::OBJECT_TYPE_HERO) != string::npos) {

			info = new HeroLoadInfo();
		}
		else if (parParam->second.find(SerializationObjectsTypes::OBJECT_TYPE_WALL) != string::npos) {

			info = new WallLoadInfo();
		}
		else if (parParam->second.find(SerializationObjectsTypes::OBJECT_TYPE_SPRITE) != string::npos) {
			info = new SpriteRendLoadInfo();
		}
		else if (parParam->second.find(SerializationObjectsTypes::OBJECT_TYPE_AA_PROJECTILE) != string::npos) {
			info = new AAProjectileLoadInfo();
		}
		else
			throw exception("Cant parse info: uknown type");

		delete parParam;
		auto beg = params.begin();
		++beg;
		auto end = params.cend();
		for (;beg != end;++beg) {

			parParam = &ParseParamLine(*beg);
			info->WriteParam(*parParam);
			delete parParam;
		}
		return *info;
	}
	else
		throw exception("Cant parse info: missing type");
}

pair<size_t, _ObjSubsPairType>& ObjsCatalogDeserial::ParseObjSubinfo(const vector<string>& params) {
	
	if (params.size() < 2)
		throw exception("Incorrect format of object's subinfo.");

	byte subID;
	size_t objID;
	AttrsCollectn& attrs = *new AttrsCollectn();

	const pair<const string, const string>* parLine = &ParseParamLine(params[0]);
	subID = (byte)stoi(parLine->second);
	delete parLine;
	parLine = &ParseParamLine(params[1]);
	if (parLine->first.find(SerializationParDefNames::OBJECT_CATALOG_ID) == string::npos)
		throw exception("Missing catalog ID.");

	objID = stoll(parLine->second);
	delete parLine;

	auto beg = params.begin();
	auto end = params.cend();
	++beg; ++beg;
	for (;beg != end;++beg) {
		parLine = &ParseParamLine(*beg);
		attrs.push_back(parLine);
	}
	return *new pair<size_t, _ObjSubsPairType>(objID, _ObjSubsPairType(subID, new LvlObjAdditParams(attrs)));
}
const pair<const string, const string>& ObjsCatalogDeserial::ParseParamLine(const string& line) {

	size_t index = line.find(PAR_DEF_NAME_END_SYM);
	if (index == string::npos)
		throw exception("Incorrect parameter format");
	string p1 = line.substr(0, index);
	string p2 = line.substr(index + 1, line.size() - index);
	return *new pair<const string, const string>(line.substr(0, index), line.substr(index + 1, line.size() - index));
}