#pragma once

#include <Entity.h>
#include <Events.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {
	class EntitiesObserver {
	public:
		static inline ExecutedEvent<Entity> AddEntityEvent = ExecutedEvent<Entity>();
		static inline ExecutedEvent<Entity> RemoveEntityEvent = ExecutedEvent<Entity>();
		static inline NoArgsExecutedEvent UnloadEntitiesEvent = NoArgsExecutedEvent();

		static void AddEntity(Entity* entity);
		static void RemoveEntity(Entity* entity);
		static forward_list<Entity*>::const_iterator GetBeginIter();
		static forward_list<Entity*>::const_iterator GetAfterEndIter();
		/// <summary>
		/// Clear data of instantiated entities. Don't destroy any entity from list.
		/// </summary>
		static void Unload();

	private:
		EntitiesObserver();

		static inline EventHandler<Entity> AddEntityEventHan = EventHandler<Entity>(AddEntityEvent);
		static inline EventHandler<Entity> RemoveEntityEventHan = EventHandler<Entity>(RemoveEntityEvent);
		static inline NoArgsEventHandler UnloadEntitiesEventHan = NoArgsEventHandler(UnloadEntitiesEvent);
 
		static inline forward_list<Entity*> EntitiesInGameLevel = forward_list<Entity*>();
	};
}