#pragma once

#include <SFML/System.hpp>
#include <ITransformableObj.h>
#include <Events.h>
#include <AttackHitInfo.h>

using namespace sf;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	class IHitPointModule;
	class IDeathModule;


	class IAttackableObj : public virtual ITransformableObj {
	public:
		virtual ~IAttackableObj(){}

		virtual IHitPointModule&	GetHPModule() const =0;
		virtual Vector2f GetClosestPoint(Vector2f dmgDealerPos) const = 0;
		
	protected:
		IAttackableObj(){}
	};


	class IHitPointModule {
	public:
		NoArgsExecutedEvent ChangedHPEvent;

		virtual ~IHitPointModule(){}

		virtual void TakeDamage		(const AttackHitInfo& attInfo) = 0;
		virtual void SetCurrentHP	(size_t hp) = 0;
		virtual void RestoreHealth	() = 0;

		virtual size_t	GetCurrentHP()	const = 0;
		virtual size_t	GetMaxHP()		const = 0;

		IDeathModule& DeathModule;

	protected:
		IHitPointModule(IDeathModule& DeathModule);

		NoArgsEventHandler ChangedHPEvHandler=NoArgsEventHandler(ChangedHPEvent);
	};


	struct ObjectDeathEventArgs {
		ObjectDeathEventArgs(){}
	};

	struct GlObjectDeathEventArgs {
		GlObjectDeathEventArgs(const ObjectDeathEventArgs& args,IAttackableObj& Owner)
			:args(args),Owner(Owner)
		{}

		const ObjectDeathEventArgs& args;
		IAttackableObj& Owner;
	};

	class IDeathModule {
	public:
		static inline ExecutedEvent<const GlObjectDeathEventArgs> DeathEvent_global=ExecutedEvent<const GlObjectDeathEventArgs>();
		ExecutedEvent<const ObjectDeathEventArgs> DeathEvent;

		bool GetIsDeadState() const { return IsDead; }

		virtual void Death() = 0;

	protected:
		IDeathModule(IAttackableObj& Owner)
			:Owner(Owner){}

		void DeathEvExecute(const ObjectDeathEventArgs& args) {
			DeathEvHandler.Execute(args);
			DeathEventGlHandler.Execute(GlObjectDeathEventArgs(args, Owner));
		}

		bool IsDead = false;
		IAttackableObj& Owner;

	private:
		EventHandler<const ObjectDeathEventArgs> DeathEvHandler = EventHandler<const ObjectDeathEventArgs>(DeathEvent);
		static inline EventHandler<const GlObjectDeathEventArgs> DeathEventGlHandler = EventHandler<const GlObjectDeathEventArgs>(DeathEvent_global);
	};
}