
#include <LevelSerialization.h>
#include <LevelCellMapDeser.h>
#include <iostream>
#include <Engine.h>
#include <FStreamExts.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

vector<vector<LvlObjInstantiationInfo*>*>& LevelCellMapDeser::Deserialize(vector<string>& serObstrMap, size_t& columnsCount) {

	columnsCount = 0;
	vector<vector<LvlObjInstantiationInfo*>*>& map=*new vector<vector<LvlObjInstantiationInfo*>*>();
	bool startDeser = true;
	vector<LvlObjInstantiationInfo*>* newRow = nullptr;
	size_t index = 0;
	bool foundEnd=false;

	for (auto& line : serObstrMap) {

		if (startDeser) {
			
			index = line.find(LVL_CMAP_START);
			if (index != string::npos) {
				
				string row = line.substr(index + 1, line.size() - index-1);
				foundEnd = row.find(LVL_CMAP_END)!=string::npos;
				newRow = LvlObjInstantiationInfo::DeserializeRow(row);
				startDeser = false;
			}
		}
		else {
			
			index = line.find(LVL_CMAP_END);
			if (index != string::npos) {

				string row = line.substr(0, index);
				foundEnd = row.find(LVL_CMAP_END) != string::npos;
				newRow = LvlObjInstantiationInfo::DeserializeRow(row);
			}
			else {

				foundEnd = line.find(LVL_CMAP_END) != string::npos;
				newRow = LvlObjInstantiationInfo::DeserializeRow(line);
			}
		}
		if (newRow != nullptr) {
			map.push_back(newRow);
			if (newRow->size() > columnsCount)
				columnsCount = newRow->size();
		}
		if (foundEnd)
			break;
	}
	return map;
}

Vector2f LevelCellMapDeser::GetCellGlobalPosition(Vector2u mapCellPos) {

	float step = Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution;
	return Vector2f(mapCellPos.y * step, mapCellPos.x * step);
}