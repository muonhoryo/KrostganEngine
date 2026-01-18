#pragma once

#include <GameEff_Dur_EntBatStatConst_bool.h>

namespace KrostganEngine::GameObjects {

	class GameEff_Dur_Disarm : public GameEff_Dur_EntBatStatConst_bool {

	public:
		GameEff_Dur_Disarm();
		GameEff_Dur_Disarm(const GameEff_Dur_Disarm& copy);
		virtual ~GameEff_Dur_Disarm();

		IGameEffect& Clone() const override;

	protected:
		void Activate(IGameEffTarget& target) override;
		void Deactivate(IGameEffTarget& target) override;

	private:
		int AAStatsIndex = 0;
	};
}
