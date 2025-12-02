
#include <LevelManager.h>

using namespace KrostganEngine::Core;

const LevelLoadingInfo* LevelManager::GetLevelInfo() {
	return LoadedLevelInfo;
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