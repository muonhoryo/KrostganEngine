#pragma once

#include <GameEffectsSystem.h>

namespace KrostganEngine::GameObjects {
	class GameEff_Inst_AddDurEff : public IGameEffect_Instant {

	public:
		GameEff_Inst_AddDurEff(ComposeGameEff_Permanent& AddedGameEff);
		GameEff_Inst_AddDurEff(const GameEff_Inst_AddDurEff& copy);
		virtual ~GameEff_Inst_AddDurEff();

	protected:
		void Activate(IGameEffTarget& target) override;

		IGameEffect& Clone() const override;

	private:
		ComposeGameEff_Permanent& AddedGameEff;
	};
}