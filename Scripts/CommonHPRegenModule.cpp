
#include <CommonHPRegenModule.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

void CommonHPRegenModule::Regen(CallbackRecArgs_Upd& args) {

	if (IsRegen) {

		if (CooldownTimer.getElapsedTime().asSeconds() >= BattleStats.GetHPRegenTick()) {

			CooldownTimer.restart();
			size_t newHPCount = BattleStats.GetCurrentHP() + BattleStats.GetHPRegenCount();
			if (newHPCount >= BattleStats.GetMaxHP()) {
				cout << "Regen hp from " << BattleStats.GetCurrentHP() << " to " << BattleStats.GetMaxHP() << " / " << BattleStats.GetMaxHP() << endl;
				BattleStats.RestoreHealth();
				IsRegen = false;
			}
			else {
				cout << "Regen hp from " << BattleStats.GetCurrentHP() << " to " << newHPCount << " / " << BattleStats.GetMaxHP() << endl;
				BattleStats.SetCurrentHP(newHPCount);
			}
		}
	}
	else {

		if (BattleStats.GetCurrentHP() < BattleStats.GetMaxHP()) {
			IsRegen = true;
			CooldownTimer.restart();
		}
	}
}