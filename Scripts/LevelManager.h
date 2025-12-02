#pragma once

#include <LevelLoadingInfo.h>
#include <Events.h>

using namespace KrostganEngine;

namespace KrostganEngine::Core {

	class LevelManager final {

	public:
		static inline ExecutedEvent<WorldTransfObj*> InstantiateObjectEvent= ExecutedEvent<WorldTransfObj*>();
		static inline ExecutedEvent<const LevelLoadingInfo&> LoadLevelEvent = ExecutedEvent<const LevelLoadingInfo&>();

		static const LevelLoadingInfo* GetLevelInfo();

		static void AssignLevelInfo(const LevelLoadingInfo& info);
		static void UnassignLevelInfo();

	private:
		LevelManager(){}

		static inline EventHandler<WorldTransfObj*> InstantiateObjEvHandler = EventHandler<WorldTransfObj*>(InstantiateObjectEvent);
		static inline EventHandler<const LevelLoadingInfo&> LoadLevelEventHandler = EventHandler<const LevelLoadingInfo&>(LoadLevelEvent);

		static inline const LevelLoadingInfo* LoadedLevelInfo = nullptr;

		friend class WorldObjectLoadInfo;
	};
}