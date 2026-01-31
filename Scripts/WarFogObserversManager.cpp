
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

void WarFogObserversManager::OnAddCallback(WarFogObserver const& callbck) {

	NeedToSort = true;
}

/// <summary>
/// Return true if target in observing range by entities of input fraction. If maxRange less then eps than set it as FLT_MAX
/// </summary>
/// <param name="pos"></param>
/// <param name="observersFraction"></param>
/// <returns></returns>
bool WarFogObserversManager::Intersect(Vector2f pos, FractionWrapper observersFraction, float maxRange) {

	if (maxRange <= eps)
		maxRange = FLT_MAX;

	if (!WarFogStencilGen::GetActivity() && FractionsSystem::GetRelationToPlayer(observersFraction) == Relation::Ally)
		return true;

	IntersectInput input;
	input.Position = Vector2i(pos/Engine::GetGlobalConsts().WarFogObserversManager_PosHashCellSize);
	input.Fraction_old = observersFraction;


	CircleCollShape obsr = CircleCollShape(DEFAULT_POSITION, 0);
	const WarFogObserver* clbk = nullptr;

	if (CachedObservers.contains(input)) {

		clbk = CachedObservers[input]->GetPtr_t_c();
		if (clbk != nullptr) {

			obsr.Center = clbk->GetGlobalPosition();
			obsr.Radius = clbk->GetObservingRange();
			if (obsr.Radius > maxRange)
				obsr.Radius = maxRange;

			if (obsr.IsPointInCollider(pos)) {

				DeleteDelayedCallbacks();
				return true;
			}
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

		if (*it == nullptr) {
			++it;
			continue;
		}

		if ((*it)->GetFraction() == observersFraction)
			break;
		else
			++it;
	}


	while (it != end) {

		if (*it == nullptr) {
			++it;
			continue;
		}

		clbk = *it;
		if (clbk->GetFraction() != observersFraction) {

			IsIteratingCallbacks = false;
			DeleteDelayedCallbacks();
			return false;
		}
		else {
			obsr.Center = clbk->GetGlobalPosition();
			obsr.Radius = clbk->GetObservingRange();
			if (obsr.Radius > maxRange)
				obsr.Radius = maxRange;

			if (obsr.IsPointInCollider(pos)) {

				if (CachedObservers.size() >= Engine::GetGlobalConsts().WarFogObserversManager_CacheSize) {

					CachedObservers.clear();
					cout << "WarFogObserversManager: Reset cached observers" << endl;
				}
				auto& ptr = clbk->GetPtr_c();
				CachedObservers[input]=new watch_ptr_handler_wr_c<WarFogObserver>(ptr);

				IsIteratingCallbacks = false;
				DeleteDelayedCallbacks();
				return true;
			}
		}
		++it;
	}

	IsIteratingCallbacks = false;
	DeleteDelayedCallbacks();

	return false;
}

void WarFogObserversManager::Set_NeedToSort() {
	NeedToSort = true;
}