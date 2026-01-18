#pragma once

#include <AutoAttackStats.h>

using namespace std;
using namespace KrostganEngine;

#define EntityBattleStatType EntBatStats_Consts::StatType

namespace KrostganEngine::GameObjects {

	struct EntBatStats_Consts{

		static inline const size_t FIELDS_COUNT_F	= 6;
		static inline const size_t FIELDS_COUNT_S_T = 2;
		static inline const size_t FIELDS_COUNT_BOOL = 3;
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
			RegenHP_Tick		= t_float | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			MovingSpeed			= t_float | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			AutoAggrRange		= t_float | (3 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			ObservingRange		= t_float | (4 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Stealth				= t_float | (5 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Resistance_MindAtt	= t_float | (6 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			//bool
			IsTargetableForAA	= t_bool | (1 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Ghostliness			= t_bool | (2 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT),
			Disarmed			= t_bool | (3 << ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT)
		};
		static inline const array<pair<StatType, string>, FIELDS_COUNT> StatTypeNames{
				pair<StatType,string>(StatType::MaxHP,				"MaxHP"),
				pair<StatType,string>(StatType::RegenHP_Amount,		"RegenHP_Amount"),
				pair<StatType,string>(StatType::RegenHP_Tick,		"RegenHP_Tick"),
				pair<StatType,string>(StatType::MovingSpeed,		"MovingSpeed"),
				pair<StatType,string>(StatType::AutoAggrRange,		"AutoAggrRange"),
				pair<StatType,string>(StatType::ObservingRange,		"ObservingRange"),
				pair<StatType,string>(StatType::Stealth,			"Stealth"),
				pair<StatType,string>(StatType::Resistance_MindAtt,	"Resistance_MindAtt"),
				pair<StatType,string>(StatType::IsTargetableForAA,	"IsTargetableForAA"),
				pair<StatType,string>(StatType::Ghostliness,		"Ghostliness"),
				pair<StatType,string>(StatType::Disarmed,			"Disarmed")
		};
	};

	

	struct EntityBattleStats final : 
		public ModifiableStatsWrapper< EntBatStats_Consts::StatType, EntBatStats_Consts::FIELDS_COUNT, EntBatStats_Consts::StatTypeNames,
				EntBatStats_Consts::FIELDS_COUNT_F, EntBatStats_Consts::FIELDS_COUNT_S_T, EntBatStats_Consts::FIELDS_COUNT_BOOL>{

	public:
		/// <summary>
		/// Initialize stats with its default values
		/// </summary>
		EntityBattleStats(AutoAttackStats* AAStats = nullptr);
		/// <summary>
		/// Initialize stats with its default values.
		/// </summary>
		/// <param name="AAStats"></param>
		EntityBattleStats(const vector<AutoAttackStats*>& AAStats);
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
		void InitializeDefaultStats();

//
//
// AutoAttackStats
//
//

	private:
		struct OnChagedStat_Disarming : public IEventSubscriber<int> {

			OnChagedStat_Disarming(EntityBattleStats& Owner) 
				:Owner(Owner){

			}

			void Execute(int& args) override {

				if (args == (int)EntityBattleStatType::Disarmed) {

					if (Owner.GetState_Disarmed()) {

						Owner.SetAAStats(-1);
					}
					else if(Owner.GetSavedAAStatsCount()>0){
						Owner.SetAAStats(0);
					}
				}
			}

		private:
			EntityBattleStats& Owner;
		};

	public:
		AutoAttackStats* GetCurrAAStats() const;
		size_t GetSavedAAStatsCount() const;
		int GetCurrAAStatsIndex() const;

		void SetAAStats(int index);
		void SetAAStats(const AutoAttackStats* stats);
		/// <summary>
		/// Return index of input stats in SavedAAStats
		/// </summary>
		/// <param name="stats"></param>
		/// <returns></returns>
		int AddAAStats(AutoAttackStats& stats);
		void RemoveAAStats(const AutoAttackStats& stats);
		void RemoveAAStats(size_t index);

		ExecutedEvent<const int> ChangeCurrAAStatsEvent = ExecutedEvent<const int>();

	private:
		/// <summary>
		/// Index of current used AutoAttackStats in vector of saved AutoAttackStats's. 
		/// -1 is define absent or turned-off auto-attack func.
		/// </summary>
		int CurrAAStats = -1;
		vector<AutoAttackStats*> SavedAAStats;
		OnChagedStat_Disarming DisarmingCheckEvSubs = OnChagedStat_Disarming(*this);

		EventHandler<const int> ChangeCurrAAStatsEventHan = EventHandler<const int>(ChangeCurrAAStatsEvent);

//
//
// Parameter's definition
//
//


//
//
// Getters
//
//

	public:
	//size_t
		Parameter<size_t> const&	GetMaxHP()			const { return *GetParameterByType_s_t(EntityBattleStatType::MaxHP); }

		//Amount of restored hp in 1 tick
		Parameter<size_t> const&	GetHPRegenAmount()	const { return *GetParameterByType_s_t(EntityBattleStatType::RegenHP_Amount); }

	//float
		//Cooldown between hp's restoring by regeneration
		Parameter<float> const&		GetHPRegenTick()		const { return *GetParameterByType_f(EntityBattleStatType::RegenHP_Tick); }

		Parameter<float> const&		GetMovingSpeed()		const { return *GetParameterByType_f(EntityBattleStatType::MovingSpeed); }

		Parameter<float> const&		GetAutoAggrRange()		const { return *GetParameterByType_f(EntityBattleStatType::AutoAggrRange); }

		Parameter<float> const&		GetObservingRange()		const {return *GetParameterByType_f(EntityBattleStatType::ObservingRange); }

		Parameter<float> const&		GetStealth()			const {return *GetParameterByType_f(EntityBattleStatType::Stealth); }

		Parameter<float> const&		GetResistance_MindAtt()	const {return *GetParameterByType_f(EntityBattleStatType::Resistance_MindAtt); }

	//bool
		const bool&		GetState_IsTargetableForAA()	const { return *GetFieldRef_bool(EntityBattleStatType::IsTargetableForAA); }

		const bool&		GetState_Ghostliness()			const {return *GetFieldRef_bool(EntityBattleStatType::Ghostliness);}

		const bool&		GetState_Disarmed()				const { return *GetFieldRef_bool(EntityBattleStatType::Disarmed); }

//
//
// Setters (default)
//
//

		void SetMaxHP(size_t hp);
		void SetHPRegenAmount(size_t amount);

		void SetHPRegenTick(float tick);
		void SetMovingSpeed(float speed);
		void SetAutoAggrRange(float range);
		void SetObservingRange(float range);
		void SetStealth(float stealth);
		void SetResistance_MindAtt(float resistance);

		void SetTargetableForAA(bool isTargetable);
		void SetGhostliness(bool ghostliness);
		void SetDisarmed(bool disarmed);

	};

	typedef ParamModifier<EntBatStats_Consts::StatType>				BatStatsParamModif;
	typedef ParamModifier_Mul<EntBatStats_Consts::StatType>			BatStatsParamModif_Mul;
	typedef ParamModifier_Sum<EntBatStats_Consts::StatType, float>	BatStatsParamModif_Sum_f;
	typedef ParamModifier_Sum<EntBatStats_Consts::StatType, size_t>	BatStatsParamModif_Sum_s_t;
}