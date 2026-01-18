#pragma once

#include <GameEffectsSystem.h>
#include <EntityBattleStats.h>

namespace KrostganEngine::GameObjects {

	class GameEff_Dur_EntBatStatMult : public IGameEffect_Durable {

	public:
		GameEff_Dur_EntBatStatMult(EntityBattleStatType StatType, float MultValue);
		GameEff_Dur_EntBatStatMult(const GameEff_Dur_EntBatStatMult& copy);
		virtual ~GameEff_Dur_EntBatStatMult();

		IGameEffect& Clone() const override;

	protected:
		void Activate(IGameEffTarget& target) override;
		void Deactivate(IGameEffTarget& target) override;

	private:
		BatStatsParamModif_Mul* ParamMod = nullptr;
		EntityBattleStatType StatType;
		float MultValue;
	};
}