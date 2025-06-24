
#include <EntitiesObserver.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

void EntitiesObserver::AddEntity(Entity* entity) {
	if(entity!=nullptr)
		EntitiesInGameLevel.push_front(entity);
}
void EntitiesObserver::RemoveEntity(Entity* entity) {
	if (entity != nullptr)
		EntitiesInGameLevel.remove(entity);
}
forward_list<Entity*>::const_iterator EntitiesObserver::GetBeginIter() {
	return EntitiesInGameLevel.cbegin();
}
forward_list<Entity*>::const_iterator EntitiesObserver::GetAfterEndIter() {
	return EntitiesInGameLevel.cend();
}

forward_list<Entity*> EntitiesObserver::EntitiesInGameLevel = forward_list<Entity*>();