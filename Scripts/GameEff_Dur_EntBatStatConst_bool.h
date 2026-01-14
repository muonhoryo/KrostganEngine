#pragma once

#include <GameEffectsSystem.h>
#include <EntityBattleStats.h>

namespace KrostganEngine::GameObjects {

	class GameEff_Dur_EntBatStatConst_bool: public IGameEffect_Durable {

	public:
		GameEff_Dur_EntBatStatConst_bool(EntityBattleStatType StatType, bool Value);
		GameEff_Dur_EntBatStatConst_bool(const GameEff_Dur_EntBatStatConst_bool& copy);
		virtual ~GameEff_Dur_EntBatStatConst_bool();

		IGameEffect& Clone() const override;

	protected:
		void Activate(IGameEffTarget& target) override;
		void Dectivate(IGameEffTarget& target) override;

	private:
		EntityBattleStatType StatType;
		bool Value;
	};
}