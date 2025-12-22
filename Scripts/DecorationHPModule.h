#pragma once

#include <IAttackableObj.h>
#include <ICallbackRec_Upd.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {

	class DecorationHPModule:public IHitPointModule {
	public:
		DecorationHPModule(
			size_t CurrentHP,
			size_t MaxHP,
			IDeathModule& DeathModule,
			TakeDamageAnimation& TakeDmgAnim);

		virtual ~DecorationHPModule();

		size_t	TakeDamage_Action(const AttackHitInfo& attInfo) override;
		void	SetCurrentHP(size_t hp) override;
		void	RestoreHealth() override;

		size_t			GetCurrentHP()	const override { return CurrentHP; }
		size_t			GetMaxHP()	const override { return MaxHP; }

	private:
		size_t				CurrentHP = 1;
		size_t				MaxHP = 1;
	};
}