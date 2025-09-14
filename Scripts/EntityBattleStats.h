#pragma once

#include <Events.h>
#include <array>
#include <string>
#include <CollectionsExts.h>

using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::GameObjects {
	struct EntityBattleStats {
	public:
		EntityBattleStats(){}

		static inline const short STATTYPE_TYPEDEF_BITSCOUNT = 4;
		/// <summary>
		/// First 4 bits define type of stat's field
		/// 0 - size_t
		/// 1 - float
		/// </summary>
		enum class StatType : int {
			//types
			t_size_t = 0,
			t_float = 1,
			type_mask = 15,
			//size_t
			MaxHP			= t_size_t | (1 << STATTYPE_TYPEDEF_BITSCOUNT),
			RegenHP_Amount	= t_size_t | (2 << STATTYPE_TYPEDEF_BITSCOUNT),
			AADamage		= t_size_t | (3 << STATTYPE_TYPEDEF_BITSCOUNT),
			//float
			RegenHP_Tick	= t_float | (1 << STATTYPE_TYPEDEF_BITSCOUNT),
			MovingSpeed		= t_float | (2 << STATTYPE_TYPEDEF_BITSCOUNT),
			AASpeed			= t_float | (3 << STATTYPE_TYPEDEF_BITSCOUNT),
			AARange			= t_float | (4 << STATTYPE_TYPEDEF_BITSCOUNT),
			AutoAggrRadius	= t_float | (5 << STATTYPE_TYPEDEF_BITSCOUNT)
		};
	private:
		static inline const array<pair<StatType,string>,8> StatTypeNames{
			pair<StatType,string>(StatType::MaxHP,			"MaxHP"),
			pair<StatType,string>(StatType::RegenHP_Amount,	"RegenHP_Amount"),
			pair<StatType,string>(StatType::RegenHP_Tick,	"RegenHP_Tick"),
			pair<StatType,string>(StatType::MovingSpeed,	"MovingSpeed"),
			pair<StatType,string>(StatType::AADamage,		"AADamage"),
			pair<StatType,string>(StatType::AASpeed,		"AASpeed"),
			pair<StatType,string>(StatType::AARange,		"AARange"),
			pair<StatType,string>(StatType::AutoAggrRadius,	"AutoAggrRadius")
		};

		struct GetStatTypeCond : public CollectionsExts::Predicate<const pair<StatType,string>&> {

			GetStatTypeCond(const string& name)
				:name(name)
			{}

			virtual bool Condition(const pair<StatType, string>& input) const override {
				return name.find(input.second)!=string::npos;
			}
		private:
			const string& name;
		};

	public:
		static const string& StatToStr(StatType type) {
			for (auto& pr : StatTypeNames) {
				if (pr.first == type)
					return pr.second;
			}
			return "";
		}
		static StatType StrToStat(const string& str) {
			
			auto cond = new GetStatTypeCond(str);
			auto type= CollectionsExts::Get_c(StatTypeNames, *cond);
			delete cond;
			return (type==nullptr)? (StatType)-1 : (type->first);
		}

		void CopyTo(EntityBattleStats& tocopy) const;
		static StatType		GetFieldType(StatType type);
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const size_t*	GetFieldRef_s_t(StatType type) const;
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const float*	GetFieldRef_f(StatType type) const;
		const void*		GetFieldRef(StatType type) const;

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
		float	GetAARange()		const { return AARange; }
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
		float	AARange			=	0;
		//View
		float	AutoAggrRadius	=	0;
	};
}