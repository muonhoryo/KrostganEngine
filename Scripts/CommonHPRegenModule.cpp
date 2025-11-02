
#include <CommonHPRegenModule.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

CommonHPRegenModule::CommonHPRegenModule(EntityHPModule& HPModule) : HPRegenModule(HPModule) {

	CooldownTimer.restart();
}

void CommonHPRegenModule::Regen(CallbackRecArgs_Upd& args) {

	auto& stats = HPModule.GetStats();
	size_t curHP = HPModule.GetCurrentHP();
	size_t maxHP = stats.GetMaxHP();
	if (IsRegen) {

		float time = CooldownTimer.getElapsedTime().asSeconds();
		float tick = stats.GetHPRegenTick();
		size_t regCount = stats.GetHPRegenAmount();
		if (time>= tick) {

			CooldownTimer.restart();
			size_t newHPCount = curHP + regCount;
			if (newHPCount >= maxHP) {
				cout << "Regen hp from " << curHP << " to " << maxHP<< " / " << maxHP << endl;
				HPModule.RestoreHealth();
				IsRegen = false;
			}
			else {
				cout << "Regen hp from " << curHP<< " to " << newHPCount << " / " << maxHP << endl;
				HPModule.SetCurrentHP(newHPCount);
			}
		}
	}
	else {

		if (curHP < maxHP) {
			IsRegen = true;
			CooldownTimer.restart();
		}
	}
}