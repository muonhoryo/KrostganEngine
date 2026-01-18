
#include <LevelManager.h>
#include <Engine.h>

using namespace KrostganEngine::Core;

const LevelLoadingInfo* LevelManager::GetLevelInfo() {
	return LoadedLevelInfo;
}
Vector2f LevelManager::GetCenterOfLevel(const LevelLoadingInfo& levelInfo) {
	float cellSize = Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution;
	cellSize /= 2;
	return Vector2f((float)levelInfo.MapColumnsCount * cellSize, (float)levelInfo.MapRowsCount * cellSize);
}
Vector2f LevelManager::GetCenterOfLevel() {
	auto lvlInfo = GetLevelInfo();
	return lvlInfo == nullptr ? Vector2f(0, 0): GetCenterOfLevel(*lvlInfo);
}

void LevelManager::AssignLevelInfo(const LevelLoadingInfo& info) {
	if (LoadedLevelInfo != nullptr)
		throw exception("Level info is already assigned");

	LoadedLevelInfo = &info;
	LoadLevelEventHandler.Execute(*LoadedLevelInfo);
}
void LevelManager::UnassignLevelInfo() {
	if (LoadedLevelInfo == nullptr)
		throw exception("Level info is not assigned");

	delete LoadedLevelInfo;
	LoadedLevelInfo = nullptr;
}