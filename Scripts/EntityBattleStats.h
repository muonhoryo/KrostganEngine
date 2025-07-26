#pragma once

#include <Events.h>

namespace KrostganEngine::GameObjects {
	struct EntityBattleStats {
	public:
		EntityBattleStats(){}

		enum class StatType {
			MaxHP,
			RegenHP_Amount,
			RegenHP_Tick,
			MovingSpeed,
			AADamage,
			AASpeed,
			AARadius,
			AutoAggrRadius
		};

		ExecutedEvent<StatType> StatChangedEvent;

	private:
		EventHandler<StatType> StatChangedEventHan = EventHandler<StatType>(StatChangedEvent);

	public:

		static	float	GetAACooldown	(float AASpeed) { return (float)1 / AASpeed; }
		//HitPoint
		size_t	GetMaxHP()			const { return MaxHP; }

		size_t	GetHPRegenCount()	const { return RegenHP_Amount; }
		float	GetHPRegenTick()	const { return RegenHP_Tick; }
		//Moving
		float	GetMovingSpeed()	const { return MovingSpeed; }
		//Attack
		size_t	GetAADamage()		const { return AADamage; }
		float	GetAASpeed()		const { return AASpeed; }
		float	GetAACooldown()		const { return GetAACooldown(AASpeed); }
		float	GetAARadius()		const { return AARadius; }
		//View
		float	GetAutoAggrRadius()	const { return AutoAggrRadius; }

		//HitPoint
		void SetMaxHP(size_t hp);
		void SetHPRegenAmount(size_t amount);
		void SetHPRegenTick(float tick);
		//Moving
		void SetMovingSpeed(float speed);
		//Attack
		void SetAADamage(size_t damage);
		void SetAASpeed(float speed);
		void SetAARadius(float radius);
		//View
		void SetAutoAggrRadius(float radius);


	private:
		//HitPoint
		size_t	MaxHP			=	1;
		size_t	RegenHP_Amount	=	1;		//Amount of restored hp in 1 tick
		float	RegenHP_Tick	=	1;		//Cooldown between hp's restoring by regeneration
		//Moving
		float	MovingSpeed		=	1;
		//Attack
		size_t	AADamage		=	0;
		float	AASpeed			=	0;		//Amount of dealt attack in 1 second
		float	AARadius		=	0;
		//View
		float	AutoAggrRadius	=	0;
	};
}