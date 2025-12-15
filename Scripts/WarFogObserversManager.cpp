
#include <WarFogObserversManager.h>
#include <ColliderShapes.h>

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

bool WarFogObserversManager::Intersect(Vector2f pos, Fraction observersFraction) {

	IsIteratingCallbacks = true;
	if (NeedToSort) {
		Callbacks.sort(WarFogObsrsSortPredicate);
		NeedToSort = false;
	}
	
	CircleCollShape obsr= CircleCollShape(DEFAULT_POSITION,0);

	auto it = Callbacks.begin();
	auto end = Callbacks.end();

	while (it != end) {

		if ((*it)->GetFraction() == observersFraction)
			break;
		else
			++it;
	}

	const WarFogObserver* clbk = nullptr;

	while (it != end) {
		clbk = *it;
		if (clbk->GetFraction() != observersFraction)
			return false;
		else {
			obsr.Center = clbk->GetGlobalPosition();
			obsr.Radius = clbk->GetObservingRange();
			if (obsr.IsPointInCollider(pos))
				return true;
		}
		++it;
	}
	return false;
}