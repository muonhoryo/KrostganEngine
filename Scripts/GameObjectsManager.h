#pragma once

#include <Entity.h>

using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Core {
	class GameObjectsManager {
	public:
		static void AddEntity(Entity* entity);
		static void RemoveEntity(Entity* entity);
		static forward_list<Entity*>::const_iterator GetBeginIter();
		static forward_list<Entity*>::const_iterator GetAfterEndIter();

	private:
		GameObjectsManager();

		static forward_list<Entity*> EntitiesInGameLevel;
	};
}