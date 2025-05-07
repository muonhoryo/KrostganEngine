#pragma once

#include <Events.h>

namespace KrostganEngine::GameObjects {
	struct ObjectDeathEventArgs {
		ObjectDeathEventArgs();
	};
	class IHitPointModule {
	public:
		ExecutedEvent<ObjectDeathEventArgs> DeathEvent;

		bool GetIsDeadState() const { return IsDead; }

		virtual void TakeDamage(size_t damage)=0;
		virtual void Death() = 0;

	protected:
		IHitPointModule();
		EventHandler<ObjectDeathEventArgs> DeathEvHandler;

		bool IsDead = false;
	};
}