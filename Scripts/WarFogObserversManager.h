#pragma once

#include <WarFogObserver.h>
#include <EngineWorkCycleModule.h>
#include <unordered_map>

using namespace std;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Core {

	struct IntersectInput final {
		Vector2i Position = (Vector2i)DEFAULT_POSITION;
		FractionWrapper Fraction_old = FractionWrapper();

		bool operator < (const IntersectInput& other) const {
			return (Position.x < other.Position.x ||
				(Position.x == other.Position.x && Position.y < other.Position.y) ||
				(Position.x == other.Position.x && Position.y == other.Position.y && Fraction_old < other.Fraction_old));
		}
		bool operator == (const IntersectInput& other) const {
			return Position == other.Position && Fraction_old == other.Fraction_old;
		}
	};

}

namespace std {

	template <>
	struct hash<KrostganEngine::Core::IntersectInput>
	{
		size_t operator()(const KrostganEngine::Core::IntersectInput& k) const noexcept
		{

			return ((hash<int>()(k.Position.x)
				^ (hash<int>()(k.Position.y) << 1)) >> 1)
				^ (hash<int>()((int)k.Fraction_old) << 1);
		}
	};
}

namespace KrostganEngine::Core {


	static bool WarFogObsrsSortPredicate(const WarFogObserver* const& first, const WarFogObserver* const& second) {

		if (first == nullptr)
			return true;
		if (second == nullptr)
			return false;
		return ((int)first->GetFraction()) < ((int)second->GetFraction());
	}

	class WarFogObserversManager final : public EngineCallbackHandler<const WarFogObserver> {

	public:
		WarFogObserversManager();

		bool Intersect(Vector2f pos, FractionWrapper observersFraction, float maxRange = FLT_MAX);
		void Set_NeedToSort();

		static WarFogObserversManager* GetInstance() {
			return Singleton;
		}

	protected:
		void OnAddCallback(WarFogObserver const& callbck) override;

	private:
		~WarFogObserversManager(){}
		bool NeedToSort = false;

		unordered_map<IntersectInput, watch_ptr_handler_wr_c<WarFogObserver>*> CachedObservers;

		static inline WarFogObserversManager* Singleton = nullptr;
	};
}
