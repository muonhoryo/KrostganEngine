#pragma once

#include <SFML/System.hpp>
#include <EntityHPModule.h>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class CommonHPRegenModule :public HPRegenModule {

	public:
		CommonHPRegenModule(EntityBattleStats& BattleStats) : HPRegenModule(BattleStats){

			CooldownTimer.restart();
		}

		void Regen(CallbackRecArgs_Upd& args) override;

	private:
		Clock CooldownTimer;
		bool IsRegen = false;
	};
}