#pragma once

#include <Entity.h>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {
	class EntitiesObserver {
	public:
		static void AddEntity(Entity* entity);
		static void RemoveEntity(Entity* entity);
		static forward_list<Entity*>::const_iterator GetBeginIter();
		static forward_list<Entity*>::const_iterator GetAfterEndIter();

	private:
		EntitiesObserver();

		static forward_list<Entity*> EntitiesInGameLevel;
	};
}