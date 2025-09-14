
#include <LevelSerialization.h>
#include <LevelCellMapDeser.h>
#include <iostream>
#include <Engine.h>
#include <FStreamExts.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

LevelCellMapDeser::CellInfo::CellInfo()
	:CatalogID(ObjectsCatalog::EMPTY_CATALOG_ID),
	SubCatalogID(ObjectsCatalog::ABSENT_SUB_CATALOG_ID)
{}

vector<vector<LevelCellMapDeser::CellInfo*>*>& LevelCellMapDeser::Deserialize(vector<string>& serObstrMap, size_t* rowsCount) {

	vector<vector<LevelCellMapDeser::CellInfo*>*>& map=*new vector<vector<LevelCellMapDeser::CellInfo*>*>();
	bool startDeser = true;
	vector<LevelCellMapDeser::CellInfo*>* newRow = nullptr;
	size_t index = 0;
	bool foundEnd=false;

	for (auto& line : serObstrMap) {

		if (startDeser) {
			
			index = line.find(LVL_CMAP_START);
			if (index != string::npos) {
				
				string row = line.substr(index + 1, line.size() - index-1);
				newRow = DeserializeRow(row, &foundEnd);
				startDeser = false;
			}
		}
		else {
			
			index = line.find(LVL_CMAP_END);
			if (index != string::npos) {

				string row = line.substr(0, index);
				newRow = DeserializeRow(row,&foundEnd);
			}
			else {
				
				newRow = DeserializeRow(line, &foundEnd);
			}
		}
		if (newRow != nullptr)
			map.push_back(newRow);
		if (foundEnd)
			break;
	}
	return map;
}
vector<LevelCellMapDeser::CellInfo*>* LevelCellMapDeser::DeserializeRow(const string& row,bool* foundEnd) {
	if (row.size() == 0)
		return nullptr;
	cout << "Deserialize map row: " << row << endl;
	vector<LevelCellMapDeser::CellInfo*>& deserRow = *new vector<LevelCellMapDeser::CellInfo*>();
	size_t start = 0;
	size_t end = 0;
	LevelCellMapDeser::CellInfo* celInf = nullptr;
	string elStr;
	size_t mapEnd = row.find(LVL_CMAP_END);
	while (true) {
		end = row.find(LVL_CMAP_ELEM_SEPARATOR, start);
		if (end>=mapEnd) {
			break;
		}
		
		elStr = row.substr(start, end - start);
		celInf = DeserializeCellInfo(elStr);
		if (celInf != nullptr)
			deserRow.push_back(celInf);
		start = end+ LVL_CMAP_ELEM_SEPARATOR.size();
	}
	if (mapEnd != string::npos) {

		*foundEnd = true;
	}
	else {
		elStr = row.substr(start, row.size() - start);
		celInf = DeserializeCellInfo(elStr);
		if (celInf != nullptr)
			deserRow.push_back(celInf);
	}
	if (deserRow.size() > 0)
		return &deserRow;
	else
	{
		delete &deserRow;
		return nullptr;
	}
}
LevelCellMapDeser::CellInfo* LevelCellMapDeser::DeserializeCellInfo(const string& str) {

	LevelCellMapDeser::CellInfo& cell = *new LevelCellMapDeser::CellInfo();
	size_t subInfoIndex = str.find(LVL_CMAP_SUBINFO_SEPARATOR);
	size_t end = str.find(LVL_CMAP_ELEM_PARAMS_DEF);
	if (end == string::npos) {		//Haven't additional params
		if (subInfoIndex != string::npos) {
			string subs = str.substr(subInfoIndex+1, end - subInfoIndex - 1);
			cell.SubCatalogID = (byte)stoi(subs);
		}
		cell.CatalogID = stoi(str);
		return &cell;
	}
	else {
		if (subInfoIndex != string::npos) {
			string subs = str.substr(subInfoIndex+1, str.length() - subInfoIndex - 2);
			cell.SubCatalogID = (byte)stoi(subs);
		}
		size_t start = 0;
		size_t sepInd = 0;
		string subStr = str.substr(start, end - 1);
		cell.CatalogID = stoi(subStr);
		start = end + LVL_CMAP_ELEM_PARAMS_DEF.size();
		const pair<const string, const string>* param = nullptr;

		//Read additional params
		while (true) {
			end = str.find(LVL_CMAP_ELEM_PARAMS_DEF,start);
			sepInd = str.find(ObjsCatalogDeserial::PAR_DEF_NAME_END_SYM, start);
			if (end == string::npos)
				break;
			subStr = str.substr(start, end - 1);
			param = new pair<const string, const string>(subStr.substr(start, sepInd), subStr.substr(sepInd + 1, subStr.size() - sepInd));
			cell.AdditionalParams.push_back(param);
			start = end + LVL_CMAP_ELEM_PARAMS_DEF.size();
		}
		subStr = str.substr(start,str.size()-start);
		param = new pair<const string, const string>(subStr.substr(start, sepInd), subStr.substr(sepInd + 1, subStr.size() - sepInd));
		cell.AdditionalParams.push_back(param);
		return &cell;
	}
}

Vector2f LevelCellMapDeser::GetCellGlobalPosition(Vector2u mapCellPos) {

	float step = Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution;
	return Vector2f(mapCellPos.y * step, mapCellPos.x * step);
}