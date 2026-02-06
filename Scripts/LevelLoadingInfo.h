#pragma once

#include <SFML/Graphics.hpp>
#include <forward_list>
#include <LvlLoadingStructs.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {

	struct LevelLoadingInfo final {

		vector<vector<LvlObjInstantiationInfo*>*>& LevelMap;
		forward_list<LvlObjInstantiationInfo*>& UniqueObjects;
		size_t MapRowsCount = 0;
		size_t MapColumnsCount = 0;

		//Consts

		Rect<float>		CameraBorders;
		Vector2f		CameraStartPos = DEFAULT_POSITION;

		float	WarFogOffset = 0;
		string	WarFogShaderPath;
		
		string	BackgroundImagePath;
		bool	BackgroundTiled = false;

		LevelLoadingInfo(vector<vector<LvlObjInstantiationInfo*>*>& LevelMap, forward_list<LvlObjInstantiationInfo*>& UniqueObjects)
			:LevelMap(LevelMap),
			UniqueObjects(UniqueObjects)
		{}
		~LevelLoadingInfo() {

			for (auto row : LevelMap) {
				for (auto obj : *row) {
					delete obj;
				}
				delete row;
			}

			for (auto obj : UniqueObjects) {
				delete obj;
			}
			
			delete &LevelMap;
			delete &UniqueObjects;
		}
	};
}


