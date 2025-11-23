#pragma once

#include <ValueDepend_EntBattStats.h>

namespace KrostganEngine::GameObjects {

	class EntityStatsWrGettingFuncs final{

	private:
		class GetWrapperFunc_Base final : public GetEntStatsWrapperFunc {

		public:
			GetWrapperFunc_Base() {}

			IModifiableStatsWrapper* GetStatsWrapper(Entity* entity) const override {
				if (entity == nullptr)
					return nullptr;
				return &entity->GetBattleStats();
			}
		};
		class GetWrapperFunc_AutoAttack final : public GetEntStatsWrapperFunc {

		public:
			GetWrapperFunc_AutoAttack() {}

			IModifiableStatsWrapper* GetStatsWrapper(Entity* entity) const override {
				if (entity == nullptr)
					return nullptr;
				return entity->GetBattleStats().GetCurrAAStats();
			}
		};

		EntityStatsWrGettingFuncs() {};



	public:
		static inline const GetEntStatsWrapperFunc& GetBaseStatsFunc = *new GetWrapperFunc_Base();
		static inline const GetEntStatsWrapperFunc& GetAutoAttackStatsFunc = *new GetWrapperFunc_AutoAttack();
	};
}