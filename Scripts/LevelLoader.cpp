
#include <EngineCore.h>
#include <CoreGameObjects.h>
#include <forward_list>
#include <SFML/Graphics.hpp>
#include <string>
#include <Events.h>
#include <SFML/System.hpp>
#include <WarFogStencilGen.h>
#include <WarFog.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

void LevelLoader::LoadLevel(const LevelLoadingInfo& levelInfo) {


	auto& consts = Engine::GetGlobalConsts();

	Vector2f mapSize = Vector2f(

		levelInfo.MapColumnsCount * consts.GameObjs_OneSizeSpriteResolution,
		levelInfo.MapRowsCount * consts.GameObjs_OneSizeSpriteResolution
	);

	//Instantiate war fog
	float warFogOffset = levelInfo.WarFogOffset;
	Vector2f warFogMin = Vector2f(-warFogOffset, -warFogOffset);
	Vector2f warFogMax = Vector2f(mapSize.x + warFogOffset, mapSize.y + warFogOffset);
	new WarFogStencilGen(warFogMin, warFogMax, Engine::GetEngineConfig().WarForStencilShaderPath);
	auto warFogShad = new Shader();
	warFogShad->loadFromFile(levelInfo.WarFogShaderPath, Shader::Fragment);
	new WarFog(warFogMin, warFogMax, DEFAULT_RENDLAYER, warFogShad);
	//

	LvlObjInstantiationInfo* cell = nullptr;
	WorldTransfObj* obj = nullptr;
	WorldObjectLoadInfo* objInfo = nullptr;
	LvlObjAdditParams* subInfo = nullptr;
	for (int i = 0;i < levelInfo.LevelMap.size();++i) {
		for (int j = 0;j < (*levelInfo.LevelMap[i]).size();++j) {
			cell = (*levelInfo.LevelMap[i])[j];
			if (cell->CatalogID != ObjectsCatalog::EMPTY_CATALOG_ID) {

				if (cell->CatalogSubID!= ObjectsCatalog::ABSENT_SUB_CATALOG_ID) {
					subInfo = ObjectsCatalog::GetSubObjInfo(cell->CatalogID, cell->CatalogSubID);
				}

				objInfo = &ObjectsCatalog::GetObjectInfo(cell->CatalogID);
				obj = objInfo->InstantiateObject(subInfo, cell->AdditParams);
				if((Vector2i)obj->GetGlobalPosition()== ITransformableObj::NULL_POS)
					obj->SetGlobalPosition(LevelCellMapDeser::GetCellGlobalPosition(Vector2u(i, j)));
				subInfo = nullptr;
			}
		}
	}

	for (auto unObjInfo : levelInfo.UniqueObjects) {

		objInfo = &ObjectsCatalog::GetObjectInfo(unObjInfo->CatalogID);
		if (unObjInfo->CatalogSubID != ObjectsCatalog::ABSENT_SUB_CATALOG_ID)
			subInfo = ObjectsCatalog::GetSubObjInfo(unObjInfo->CatalogID, unObjInfo->CatalogSubID);
		obj = objInfo->InstantiateObject(subInfo, unObjInfo->AdditParams);
		subInfo = nullptr;
	}

	LevelBypassMapManager::LoadFromLevelMap(levelInfo.LevelMap);

	//Instantiate background
	if (levelInfo.BackgroundImagePath != "") {

		Texture& bgTex = *new Texture();
		bgTex.loadFromFile(levelInfo.BackgroundImagePath);
		SpriteRenderer& bgSprite = *new SpriteRenderer(bgTex);
		Vector2f lvlSize = Vector2f
			(-levelInfo.CameraBorders.left + levelInfo.CameraBorders.width,
			-levelInfo.CameraBorders.top + levelInfo.CameraBorders.height);
		Vector2f lvlCenter = Vector2f(lvlSize.x / 2, lvlSize.y / 2);
		lvlCenter.x += levelInfo.CameraBorders.left;
		lvlCenter.y += levelInfo.CameraBorders.top;
		pair<float, float> lvlSizeMinMax = minmax(lvlSize.x, lvlSize.y);
		float lvlSizeMinMaxRatio = lvlSizeMinMax.first / lvlSizeMinMax.second;
		bool coDirect = bgSprite.IsSpriteVertical() == (lvlSize.x < lvlSize.y);
		bool lvlRatioBigger = lvlSizeMinMaxRatio > bgSprite.GetSpriteMinMaxRatio();
		bgSprite.SetGlobalScale_Sng(lvlSizeMinMax.second / ((lvlRatioBigger ^ coDirect) ? bgSprite.GetMinSpritePixSize() : bgSprite.GetMaxSpritePixSize()));
		bgSprite.SetGlobalPosition(lvlCenter);
		bgSprite.Set_LateRender(false);
		bgSprite.SetRendLayer((std::byte)0);
	}

	LevelManager::AssignLevelInfo(levelInfo);

}