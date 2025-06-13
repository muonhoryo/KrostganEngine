#pragma once

#include <Events.h>
#include <AttackInfo.h>

namespace KrostganEngine::GameObjects {
	struct ObjectDeathEventArgs {
		ObjectDeathEventArgs();
	};
	class IHitPointModule {
	public:
		ExecutedEvent<ObjectDeathEventArgs> DeathEvent;

		bool GetIsDeadState() const { return IsDead; }

		virtual void TakeDamage(AttackInfo attInfo)=0;
		virtual void Death() = 0;

	protected:
		IHitPointModule();
		EventHandler<ObjectDeathEventArgs> DeathEvHandler;

		bool IsDead = false;
	};
}