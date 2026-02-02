#pragma once

#include <SFML/System.hpp>
#include <ITransformableObj.h>
#include <_Events.h>
#include <FractionsSystem.h>
#include <CallbackDelegates.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	class IHitPointModule;
	class IDeathModule;
	class IAttackableObj;


	struct AttackHitInfo {

		AttackHitInfo(size_t DealtDmg, watch_ptr_handler_wr<IAttackableObj> Target, 
			FractionWrapper DmgDealerFrac)
			:DealtDmg(DealtDmg),
			Target(Target),
			DmgDealerFrac(DmgDealerFrac)
		{}

		const size_t DealtDmg;
		watch_ptr_handler_wr<IAttackableObj> Target;
		FractionWrapper DmgDealerFrac = FractionWrapper();
	};

	class TakeDamageAnimation {

	public:
		virtual ~TakeDamageAnimation() {}

		virtual void OnTakeDmg(const AttackHitInfo& attInfo, size_t totalDmg) = 0;

	protected:
		TakeDamageAnimation() {}
	};


	class IAttackableObj : public virtual ITransformableObj {
	public:
		enum class AtkParam : short {
			None = 0,
			IsAA = 1
		};

		virtual ~IAttackableObj(){}

		virtual IHitPointModule&	GetHPModule() const =0;
		virtual Vector2f GetClosestPoint(Vector2f dmgDealerPos) const = 0;
		
		virtual bool IsTargetableForAA() const = 0;
		
		virtual void SetTargetableForAA(bool isTargetable) = 0;

		/// <summary>
		/// Return true if object can be attacked with given properties of attack
		/// </summary>
		/// <param name="isAA"></param>
		/// <returns></returns>
		bool CheckAttackReachability(AtkParam atkParam) const;

	protected:
		IAttackableObj(){}
	};


	class IHitPointModule {
	public:
		NoArgsExecutedEvent ChangedHPEvent;

		virtual ~IHitPointModule();

		void TakeDamage		(const AttackHitInfo& attInfo);

		virtual void SetCurrentHP	(size_t hp) = 0;
		virtual void RestoreHealth	() = 0;

		virtual size_t	GetCurrentHP()	const = 0;
		virtual size_t	GetMaxHP()		const = 0;

		IDeathModule& DeathModule;

	protected:
		IHitPointModule(IDeathModule& DeathModule, TakeDamageAnimation& TakeDmgAnim);

		NoArgsEventHandler ChangedHPEvHandler=NoArgsEventHandler(ChangedHPEvent);

		virtual size_t TakeDamage_Action(const AttackHitInfo& attInfo) = 0;

	private:
		TakeDamageAnimation& TakeDmgAnim;
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

	class DelayedDeath final : public CallbackDelegate_Upd {
	public:
		DelayedDeath(IAttackableObj& Owner) :CallbackDelegate_Upd(),
			Owner(Owner) {}

		void Execute(CallbackRecArgs_Upd args) override {
			delete& Owner;
		}
	private:
		IAttackableObj& Owner;
	};
}