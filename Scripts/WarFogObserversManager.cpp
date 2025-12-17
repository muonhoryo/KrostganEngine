
#include <WarFogObserversManager.h>
#include <ColliderShapes.h>
#include <Engine.h>
#include <WarFogStencilGen.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

WarFogObserversManager::WarFogObserversManager()
	:EngineCallbackHandler(){

	if (Singleton != nullptr)
		throw exception("WarFogObserversManager is already created");

	Singleton = this;
}

void WarFogObserversManager::OnAddCallback(WarFogObserver* const& callbck) {

	NeedToSort = true;
}

/// <summary>
/// Return true if target in observing range by entities of input fraction
/// </summary>
/// <param name="pos"></param>
/// <param name="observersFraction"></param>
/// <returns></returns>
bool WarFogObserversManager::Intersect(Vector2f pos, Fraction observersFraction) {

	if (!WarFogStencilGen::GetActivity() && FractionsSystem::GetRelationToPlayer(observersFraction) == Relation::Ally)
		return true;

	IntersectInput input;
	input.Position = Vector2i(pos/Engine::GetGlobalConsts().WarFogObserversManager_PosHashCellSize);
	input.Fraction = observersFraction;

	CircleCollShape obsr = CircleCollShape(DEFAULT_POSITION, 0);
	const WarFogObserver* clbk = nullptr;

	if (CachedObservers.contains(input)) {

		clbk = CachedObservers[input]->GetPtr_t_c();
		if (clbk != nullptr) {

			obsr.Center = clbk->GetGlobalPosition();
			obsr.Radius = clbk->GetObservingRange();
			if (obsr.IsPointInCollider(pos))
				return true;
			else {

				CachedObservers.erase(input);
			}
		}
	}

	IsIteratingCallbacks = true;
	if (NeedToSort) {
		Callbacks.sort(WarFogObsrsSortPredicate);
		NeedToSort = false;
	}
	

	auto it = Callbacks.begin();
	auto end = Callbacks.end();

	while (it != end) {

		if ((*it) == nullptr) {
			++it;
			continue;
		}

		if ((*it)->GetFraction() == observersFraction)
			break;
		else
			++it;
	}


	while (it != end) {
		if ((*it) == nullptr) {
			++it;
			continue;
		}

		clbk = *it;
		if (clbk->GetFraction() != observersFraction)
			return false;
		else {
			obsr.Center = clbk->GetGlobalPosition();
			obsr.Radius = clbk->GetObservingRange();
			if (obsr.IsPointInCollider(pos)) {

				if (CachedObservers.size() >= Engine::GetGlobalConsts().WarFogObserversManager_CacheSize)
					CachedObservers.clear();
				auto& ptr = clbk->GetPtr_c();
				CachedObservers[input]=new watch_ptr_handler_wr_c<WarFogObserver>(ptr);
				return true;
			}
		}
		++it;
	}
	return false;
}