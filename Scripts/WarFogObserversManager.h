#pragma once

#include <WarFogObserver.h>
#include <EngineWorkCycleModule.h>

namespace KrostganEngine::Core {

	static bool WarFogObsrsSortPredicate(const WarFogObserver* const& first, const WarFogObserver* const& second) {

		return (int)first->GetFraction() < (int)second->GetFraction();
	}
	class WarFogObserversManager final : public EngineCallbackHandler<const WarFogObserver> {

	public:
		WarFogObserversManager();

		bool Intersect(Vector2f pos, Fraction observersFraction);

		static WarFogObserversManager* GetInstance() {
			return Singleton;
		}

	protected:
		void OnAddCallback(WarFogObserver* const& callbck);

	private:
		~WarFogObserversManager(){}
		bool NeedToSort = false;

		static inline WarFogObserversManager* Singleton = nullptr;
	};
}