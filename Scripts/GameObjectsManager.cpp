
#include <GameObjectsManager.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

void GameObjectsManager::AddEntity(Entity* entity) {
	if(entity!=nullptr)
		EntitiesInGameLevel.push_front(entity);
}
void GameObjectsManager::RemoveEntity(Entity* entity) {
	if (entity != nullptr)
		EntitiesInGameLevel.remove(entity);
}
forward_list<Entity*>::const_iterator GameObjectsManager::GetBeginIter() {
	return EntitiesInGameLevel.cbegin();
}
forward_list<Entity*>::const_iterator GameObjectsManager::GetAfterEndIter() {
	return EntitiesInGameLevel.cend();
}

forward_list<Entity*> GameObjectsManager::EntitiesInGameLevel = forward_list<Entity*>();