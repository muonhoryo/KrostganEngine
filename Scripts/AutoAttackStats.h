#pragma once

#include <ModifiableStatsWrapper.h>

using namespace KrostganEngine;

#define AAStatType AutoAttackStats_Consts::StatType

namespace KrostganEngine::GameObjects {

	struct AutoAttackStats_Consts {

		static inline const size_t FIELDS_COUNT_F		= 2;
		static inline const size_t FIELDS_COUNT_S_T		= 1;
		static inline const size_t FIELDS_COUNT_BOOL	= 1;
		static inline const size_t FIELDS_COUNT = FIELDS_COUNT_S_T + FIELDS_COUNT_F + FIELDS_COUNT_BOOL;

		enum class StatType : int {
			//types
			t_size_t	= 0,
			t_float		= 1,
			t_bool		= 2,
			type_mask	= 15,
			//size_t
			AADamage = t_size_t | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//float
			AASpeed = t_float | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			AARange = t_float | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//bool
			IsRange = t_bool | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT)
		};
		static inline const array<pair<StatType, string>, FIELDS_COUNT> StatTypeNames{
				pair<StatType,string>(StatType::AADamage,		"AADamage"),
				pair<StatType,string>(StatType::AASpeed,		"AASpeed"),
				pair<StatType,string>(StatType::AARange,		"AARange")
		};

	private:
		AutoAttackStats_Consts(){}
	};



	struct AutoAttackStats 
		: public ModifiableStatsWrapper<AutoAttackStats_Consts::StatType, AutoAttackStats_Consts::FIELDS_COUNT, AutoAttackStats_Consts::StatTypeNames,
				AutoAttackStats_Consts::FIELDS_COUNT_F, AutoAttackStats_Consts::FIELDS_COUNT_S_T, AutoAttackStats_Consts::FIELDS_COUNT_BOOL>{
	
	public:
		AutoAttackStats();
		AutoAttackStats(const AutoAttackStats& copy)
			:ModifiableStatsWrapper(copy) {}
		virtual ~AutoAttackStats(){}

//
//
// Parameter's definition
//
//
	public:
		static	float	GetAACooldown(float AASpeed) { return (float)1 / AASpeed; }

//
//
// Getters
//
//
// 
		Parameter<size_t> const& GetAADamage()		const { return *GetParameterByType_s_t(AAStatType::AADamage); }

		//Amount of dealt attack in 1 second
		Parameter<float> const& GetAASpeed()		const { return *GetParameterByType_f(AAStatType::AASpeed); }

		float					GetAACooldown()		const { return GetAACooldown(GetAASpeed().Stat); }
		Parameter<float> const& GetAARange()		const { return *GetParameterByType_f(AAStatType::AARange); }

		const bool&				GetState_IsRange()	const {return *GetFieldRef_bool(AAStatType::IsRange); }

//
//
// Setters (default)
//
//

		void SetAADamage(size_t damage);
		void SetAASpeed(float speed);
		void SetAARange(float range);
		void SetIsRange(bool isRange);

	};

	typedef ParamModifier<AAStatType>				AAStatsParamModif;
	typedef ParamModifier_Mul<AAStatType>			AAStatsParamModif_Mul;
	typedef ParamModifier_Sum<AAStatType, float>	AAStatsParamModif_Sum_f;
	typedef ParamModifier_Sum<AAStatType, size_t>	AAStatsParamModif_Sum_s_t;
}