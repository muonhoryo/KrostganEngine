#pragma once

#include <ModifiableStatsWrapper.h>
#include <LvlLoadingStructs.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;

#define AAStatType AutoAttackStats_Consts::StatType
#define AAStatsConsts AutoAttackStats_Consts

namespace KrostganEngine::GameObjects {

	struct AutoAttackStats_Consts {

		static inline const size_t FIELDS_COUNT_F		= 4;
		static inline const size_t FIELDS_COUNT_S_T		= 1;
		static inline const size_t FIELDS_COUNT_BOOL	= 4;
		static inline const size_t FIELDS_COUNT = FIELDS_COUNT_S_T + FIELDS_COUNT_F + FIELDS_COUNT_BOOL;

		enum class StatType : int {
			//types
			t_size_t	= 0,
			t_float		= 1,
			t_bool		= 2,
			type_mask	= 15,
			//size_t
			Damage = t_size_t | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//float
			Speed = t_float | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Range = t_float | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			ProjSpeed = t_float | (3<< ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			SiegeRange= t_float | (4 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//bool
			IsRange = t_bool | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			IsSiege = t_bool | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Proj_LockRotation = t_bool | (3 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Proj_IsSelfHoming = t_bool | (4 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT)
		};
		static inline const array<pair<StatType, string>, FIELDS_COUNT> StatTypeNames{
				pair<StatType,string>(StatType::Damage,				"AADamage"),
				pair<StatType,string>(StatType::Speed,				"AASpeed"),
				pair<StatType,string>(StatType::Range,				"AARange"),
				pair<StatType,string>(StatType::ProjSpeed,			"Proj_Speed"),
				pair<StatType,string>(StatType::SiegeRange,			"AASiegeRange"),
				pair<StatType,string>(StatType::IsRange,			"IsRange"),
				pair<StatType,string>(StatType::IsSiege,			"IsSiege"),
				pair<StatType,string>(StatType::Proj_LockRotation,	"Proj_LockRotation"),
				pair<StatType,string>(StatType::Proj_IsSelfHoming,	"Proj_IsSelfHoming")
		};

	private:
		AutoAttackStats_Consts(){}
	};



	struct AutoAttackStats 
		: public ModifiableStatsWrapper<AAStatsConsts::StatType, AAStatsConsts::FIELDS_COUNT, AAStatsConsts::StatTypeNames,
				AAStatsConsts::FIELDS_COUNT_F, AAStatsConsts::FIELDS_COUNT_S_T, AAStatsConsts::FIELDS_COUNT_BOOL>{
	
	public:
		AutoAttackStats
			(const LvlObjInstantiationInfo* ProjectileInfo=nullptr,
			const LvlObjInstantiationInfo* SiegeHitEffInfo =nullptr);

		AutoAttackStats(const AutoAttackStats& copy)
			:ModifiableStatsWrapper(copy),
			ProjectileInfo(copy.ProjectileInfo),
			SiegeHitEffInfo(copy.SiegeHitEffInfo){}
		virtual ~AutoAttackStats(){}

		void CopyTo(ModifiableStatsWrapper
			<AutoAttackStats_Consts::StatType,
			AutoAttackStats_Consts::FIELDS_COUNT,
			AutoAttackStats_Consts::StatTypeNames,
			AutoAttackStats_Consts::FIELDS_COUNT_F,
			AutoAttackStats_Consts::FIELDS_COUNT_S_T,
			AutoAttackStats_Consts::FIELDS_COUNT_BOOL>& toCopy) const override;

	private:
		void CopyTo_Internal(AutoAttackStats& toCopy) const;
//
//
// Parameter's definition
//
//
	public:
		static	float	GetCooldown(float Speed) { return (float)1 / Speed; }

//
//
// Getters
//
//
// 
		Parameter<size_t> const& GetDamage()		const { return *GetParameterByType_s_t(AAStatType::Damage); }

		//Amount of dealt attack in 1 second
		Parameter<float> const& GetSpeed()		const { return *GetParameterByType_f(AAStatType::Speed); }

		float					GetCooldown()		const { return GetCooldown(GetSpeed().Stat); }
		Parameter<float> const& GetRange()		const { return *GetParameterByType_f(AAStatType::Range); }

		Parameter<float> const& GetProjSpeed()	const {return *GetParameterByType_f(AAStatType::ProjSpeed);}

		Parameter<float> const& GetSiegeRange()	const { return *GetParameterByType_f(AAStatType::SiegeRange); }

		const bool&				GetState_IsRange()	const {return *GetFieldRef_bool(AAStatType::IsRange); }

		const bool&				GetState_IsSiege()	const {return *GetFieldRef_bool(AAStatType::IsSiege); }

		const bool&				GetState_Proj_LockRotation() const { return *GetFieldRef_bool(AAStatType::Proj_LockRotation); }

		const bool&				GetState_Proj_IsSelfHoming() const { return *GetFieldRef_bool(AAStatType::Proj_IsSelfHoming); }

//
//
// Setters (default)
//
//

		void SetDamage(size_t damage);
		void SetSpeed(float speed);
		void SetRange(float range);
		void SetProjSpeed(float speed);
		void SetSiegeRange(float range);
		void SetIsRange(bool isRange);
		void SetIsSiege(bool isSiege);
		void SetProj_LockRotation(bool lockRotation);
		void SetProj_IsSelfHoming(bool isSelfHoming);

//
//
// Additional parameters
//
//

		const LvlObjInstantiationInfo& GetProjectileInfo() const { return ProjectileInfo; }
		const LvlObjInstantiationInfo& GetSiegeHitEffInfo() const { return SiegeHitEffInfo; }
		
		void SetProjectileInfo(const LvlObjInstantiationInfo& projInfo);
		void SetSiegeHitEffInfo(const LvlObjInstantiationInfo& siegeEffInho);

	private:
		LvlObjInstantiationInfo ProjectileInfo;
		LvlObjInstantiationInfo SiegeHitEffInfo;

	};

	typedef ParamModifier<AAStatType>				AAStatsParamModif;
	typedef ParamModifier_Mul<AAStatType>			AAStatsParamModif_Mul;
	typedef ParamModifier_Sum<AAStatType, float>	AAStatsParamModif_Sum_f;
	typedef ParamModifier_Sum<AAStatType, size_t>	AAStatsParamModif_Sum_s_t;
}