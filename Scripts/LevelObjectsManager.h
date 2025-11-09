#pragma once

#include <LevelLoadingInfo.h>
#include <Events.h>

using namespace KrostganEngine;

namespace KrostganEngine::Core {

	class LevelObjectsManager final {

	public:
		static inline ExecutedEvent<WorldTransfObj*> InstantiateObjectEvent= ExecutedEvent<WorldTransfObj*>();

	private:
		LevelObjectsManager(){}

		static inline EventHandler<WorldTransfObj*> InstantiateObjEvHandler = EventHandler<WorldTransfObj*>(InstantiateObjectEvent);

		friend class WorldObjectLoadInfo;
	};
}