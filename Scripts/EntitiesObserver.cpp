
#include <EntitiesObserver.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

void EntitiesObserver::AddEntity(Entity* entity) {
	if (entity != nullptr) {

		EntitiesInGameLevel.push_front(entity);
		AddEntityEventHan.Execute(*entity);
	}
}
void EntitiesObserver::RemoveEntity(Entity* entity) {
	if (entity != nullptr){

		EntitiesInGameLevel.remove(entity);
		RemoveEntityEventHan.Execute(*entity);
	}
}
forward_list<Entity*>::const_iterator EntitiesObserver::GetBeginIter() {
	return EntitiesInGameLevel.cbegin();
}
forward_list<Entity*>::const_iterator EntitiesObserver::GetAfterEndIter() {
	return EntitiesInGameLevel.cend();
}
void EntitiesObserver::Unload() {
	EntitiesInGameLevel.clear();
	UnloadEntitiesEventHan.Execute();
}