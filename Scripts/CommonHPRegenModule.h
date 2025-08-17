#pragma once

#include <SFML/System.hpp>
#include <EntityHPModule.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {
	class CommonHPRegenModule :public HPRegenModule {

	public:
		CommonHPRegenModule(KrostganEngine::GameObjects::EntityHPModule& HPModule);

	protected:
		void Regen(CallbackRecArgs_Upd& args) override;

	private:
		Clock CooldownTimer;
		bool IsRegen = false;
	};
}