#pragma once

#include <SFML/System.hpp>
#include <TransformableObj.h>
#include <Events.h>
#include <AttackInfo.h>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class IHitPointModule;
	class IDeathModule;


	class IAttackableObj : public virtual TransformableObj {
	public:
		virtual ~IAttackableObj(){}

		virtual IHitPointModule& GetHPModule()=0;
		virtual Vector2f GetClosestPoint(Vector2f dmgDealerPos) const = 0;
		
	protected:
		IAttackableObj(){}
	};


	class IHitPointModule {
	public:
		virtual ~IHitPointModule(){}

		virtual void TakeDamage		(AttackInfo attInfo) = 0;
		virtual void SetCurrentHP	(size_t hp) = 0;
		virtual void RestoreHealth	() = 0;

		virtual size_t	GetCurrentHP()	const = 0;
		virtual size_t	GetMaxHP()		const = 0;

		IDeathModule& DeathModule;

	protected:
		IHitPointModule(IDeathModule& DeathModule);
	};


	struct ObjectDeathEventArgs {
		ObjectDeathEventArgs();
	};
	class IDeathModule {
	public:
		ExecutedEvent<ObjectDeathEventArgs> DeathEvent;

		bool GetIsDeadState() const { return IsDead; }

		virtual void Death() = 0;

	protected:
		IDeathModule(IAttackableObj& Owner);
		EventHandler<ObjectDeathEventArgs> DeathEvHandler;

		bool IsDead = false;
		IAttackableObj& Owner;
	};
}