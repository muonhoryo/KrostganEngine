#pragma once

#include <AutoAttackStats.h>

using namespace std;
using namespace KrostganEngine;

#define EntityBattleStatType EntBatStats_Consts::StatType

namespace KrostganEngine::GameObjects {

	struct EntBatStats_Consts{

		static inline const size_t FIELDS_COUNT_F	= 3;
		static inline const size_t FIELDS_COUNT_S_T = 2;
		static inline const size_t FIELDS_COUNT_BOOL = 1;
		static inline const size_t FIELDS_COUNT		= FIELDS_COUNT_S_T + FIELDS_COUNT_F + FIELDS_COUNT_BOOL;

		enum class StatType : int {
			//types
			t_size_t	= 0,
			t_float		= 1,
			t_bool		= 2,
			type_mask	= 15,
			//size_t
			MaxHP			= t_size_t | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			RegenHP_Amount	= t_size_t | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//float
			RegenHP_Tick	= t_float | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			MovingSpeed		= t_float | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			AutoAggrRadius	= t_float | (3 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//bool
			IsTargetableForAA	= t_bool | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT)
		};
		static inline const array<pair<StatType, string>, FIELDS_COUNT> StatTypeNames{
				pair<StatType,string>(StatType::MaxHP,				"MaxHP"),
				pair<StatType,string>(StatType::RegenHP_Amount,		"RegenHP_Amount"),
				pair<StatType,string>(StatType::RegenHP_Tick,		"RegenHP_Tick"),
				pair<StatType,string>(StatType::MovingSpeed,		"MovingSpeed"),
				pair<StatType,string>(StatType::AutoAggrRadius,		"AutoAggrRadius"),
				pair<StatType,string>(StatType::IsTargetableForAA,	"IsTargetableForAA")
		};
	};

	

	struct EntityBattleStats : 
		public ModifiableStatsWrapper< EntBatStats_Consts::StatType, EntBatStats_Consts::FIELDS_COUNT, EntBatStats_Consts::StatTypeNames,
				EntBatStats_Consts::FIELDS_COUNT_F, EntBatStats_Consts::FIELDS_COUNT_S_T, EntBatStats_Consts::FIELDS_COUNT_BOOL>{

	public:
		/// <summary>
		/// Initialize stats with its default values
		/// </summary>
		EntityBattleStats(AutoAttackStats* AAStats = nullptr);
		EntityBattleStats(const EntityBattleStats& copy);
		virtual ~EntityBattleStats();

		void CopyTo(ModifiableStatsWrapper
			<EntBatStats_Consts::StatType,
			EntBatStats_Consts::FIELDS_COUNT,
			EntBatStats_Consts::StatTypeNames,
			EntBatStats_Consts::FIELDS_COUNT_F,
			EntBatStats_Consts::FIELDS_COUNT_S_T,
			EntBatStats_Consts::FIELDS_COUNT_BOOL>& toCopy) const override;

	private:
		void CopyTo_Internal(EntityBattleStats& toCopy) const;

		AutoAttackStats* AAStats;

//
//
// Parameter's definition
//
//

	public:

//
//
// Getters
//
//
		
	//Attack
		AutoAttackStats* GetAAStats() { return AAStats; }

	//size_t
		Parameter<size_t> const&	GetMaxHP()			const { return *GetParameterByType_s_t(EntityBattleStatType::MaxHP); }

		//Amount of restored hp in 1 tick
		Parameter<size_t> const&	GetHPRegenAmount()	const { return *GetParameterByType_s_t(EntityBattleStatType::RegenHP_Amount); }

	//float
		//Cooldown between hp's restoring by regeneration
		Parameter<float> const&		GetHPRegenTick()	const { return *GetParameterByType_f(EntityBattleStatType::RegenHP_Tick); }

		Parameter<float> const&		GetMovingSpeed()	const { return *GetParameterByType_f(EntityBattleStatType::MovingSpeed); }

		Parameter<float> const&		GetAutoAggrRadius()	const { return *GetParameterByType_f(EntityBattleStatType::AutoAggrRadius); }

	//bool
		const bool&		GetState_IsTargetableForAA() const { return *GetFieldRef_bool(EntityBattleStatType::IsTargetableForAA); }

//
//
// Setters (default)
//
//

		void SetMaxHP(size_t hp);
		void SetHPRegenAmount(size_t amount);

		void SetHPRegenTick(float tick);
		void SetMovingSpeed(float speed);
		void SetAutoAggrRadius(float radius);

		void SetTargetableForAA(bool isTargetable);

	};

	typedef ParamModifier<EntBatStats_Consts::StatType>				BatStatsParamModif;
	typedef ParamModifier_Mul<EntBatStats_Consts::StatType>			BatStatsParamModif_Mul;
	typedef ParamModifier_Sum<EntBatStats_Consts::StatType, float>	BatStatsParamModif_Sum_f;
	typedef ParamModifier_Sum<EntBatStats_Consts::StatType, size_t>	BatStatsParamModif_Sum_s_t;
}