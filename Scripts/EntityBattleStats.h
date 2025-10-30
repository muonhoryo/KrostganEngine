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
		EntityBattleStats(const EntityBattleStats& copy) 
			:EntityBattleStats(){

			copy.CopyTo(*this);
		}
		virtual ~EntityBattleStats();

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
			auto type = CollectionsExts::Get_c(StatTypeNames, *cond);
			delete cond;
			return (type == nullptr) ? (StatType)-1 : (type->first);
		}

//
//
// Parameter's modifiers
//
//

	public:
		template<typename TValueType>
		struct Parameter final {
		public:
			explicit Parameter(TValueType Default)
				:Default(Default),
				Stat(Default)
			{}

			TValueType GetStat() const { return Stat; }
			TValueType GetDefault() const { return Default; }

			TValueType const& GetRef_Stat() const { return Stat; }
			TValueType const& GetRef_Default() const { return Default; }

			operator TValueType() const {
				return Stat;
			}

		private:
			TValueType Stat;
			TValueType Default;

			friend class EntityBattleStats;
		};
		
		struct ParamModifier {

			enum class ModOpType : char {
				PreSum,
				Mul,
				PostSum
			};

			const ModOpType ModOp;
			const EntityBattleStats::StatType FieldType;

		protected:
			ParamModifier(ModOpType ModOp, EntityBattleStats::StatType FieldType)
				:ModOp(ModOp),
				FieldType(FieldType)
			{}
		};
		struct ParamModifier_Mul final : public ParamModifier{

			ParamModifier_Mul(EntityBattleStats::StatType FieldType,float MulCoef)
				:ParamModifier(ModOpType::Mul,FieldType),
				MulCoef(MulCoef)
			{}

			float MulCoef;
		};
		template<typename TValueType>
		struct ParamModifier_Sum final: public ParamModifier {

			ParamModifier_Sum(EntityBattleStats::StatType FieldType, TValueType SumValue,bool isPostSum)
				:ParamModifier(isPostSum?ModOpType::PostSum:ModOpType::PreSum, FieldType),
				SumValue(SumValue)
			{}

			TValueType SumValue;
		};

	private:
		struct ParamModifier_SortFunc final : CollectionsExts::CompareFunc<const ParamModifier*> {

			bool Compare(const ParamModifier* const& first, const ParamModifier* const& second) const override {

				int firstType = (int)first->FieldType;
				int secondType = (int)second->FieldType;
				if (firstType == secondType) {

					int firstOp = (int)first->ModOp;
					int secondOp = (int)second->ModOp;
					return firstOp < secondOp;
				}
				else
					return firstType < secondType;
			}
		};
		static inline const ParamModifier_SortFunc ParamModsSortFuncInstance= ParamModifier_SortFunc();

		vector<const ParamModifier*> ParamModifiers;

		void RecalculateStat(StatType type);
		template<typename TFieldType>
		void RecalculateStat_t(StatType type, Parameter<TFieldType> const& param) {

			TFieldType& field = *const_cast<TFieldType*>(&param.GetRef_Stat());
			TFieldType const& defaultField = param.GetRef_Default();

			field = defaultField;

			auto it = ParamModifiers.begin();
			auto itEnd = ParamModifiers.end();
			const ParamModifier* mod = nullptr;

			//Find stat's modifiers
			while (it != itEnd) {
				mod = *it;
				if (mod->FieldType == type) {
					break;
				}
				++it;
			}

			if (it == itEnd)
				return;

			//Pre sum
			{
				const ParamModifier_Sum<TFieldType>* modSum = nullptr;
				while (it != itEnd) {
					mod = *it;
					if (mod->ModOp != ParamModifier::ModOpType::PreSum ||
						mod->FieldType!=type) {
						break;
					}
					else {
						modSum = static_cast<const ParamModifier_Sum<TFieldType>*>(mod);
						field += modSum->SumValue;
						++it;
					}
				}
			}

			if (it == itEnd ||
				(mod!=nullptr &&
				mod->FieldType != type))
				return;

			//Multiply
			{
				const ParamModifier_Mul* modMul = nullptr;
				float mulSumCoef = 1;
				while (it != itEnd) {
					mod = *it;
					if (mod->ModOp != ParamModifier::ModOpType::Mul ||
						mod->FieldType != type) {
						break;
					}
					else {
						modMul = static_cast<const ParamModifier_Mul*>(mod);
						mulSumCoef *= modMul->MulCoef;
						++it;
					}
				}
				field *= mulSumCoef;
			}

			if (it == itEnd ||
				(mod!=nullptr &&
				mod->FieldType != type))
				return;

			//Post sum
			const ParamModifier_Sum<TFieldType>* modPostSum = nullptr;
			while (it != itEnd) {
				mod = *it;
				if (mod->FieldType != type) {
					break;
				}
				else {
					modPostSum = static_cast<const ParamModifier_Sum<TFieldType>*>(mod);
					field += modPostSum->SumValue;
					++it;
				}
			}
		}

	public:
		void AddModifier(const ParamModifier& mod);
		void RemoveModifier(const ParamModifier& mod);
		
//
//
// Parameter field's getting
//
//

	public:
		/// <summary>
		/// Copy parameters of this stats to target stats
		/// </summary>
		/// <param name="tocopy"></param>
		void CopyTo(EntityBattleStats& tocopy) const;
		static StatType		GetFieldType(StatType type);
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const size_t*	GetFieldRef_s_t(StatType type,bool isDefField=false) const;
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const float*	GetFieldRef_f(StatType type, bool isDefField = false) const;
		const void*		GetFieldRef(StatType type, bool isDefField = false) const;

		ExecutedEvent<const StatType> StatChangedEvent = ExecutedEvent<const StatType>();
		ExecutedEvent<const StatType> DefaultStatChangedEvent = ExecutedEvent<const StatType>();

	private:
		EventHandler<const StatType> StatChangedEventHan = EventHandler<const StatType>(StatChangedEvent);
		EventHandler<const StatType> DefaultStatChangedEventHan = EventHandler<const StatType>(DefaultStatChangedEvent);

		template<typename TFieldType>
		static TFieldType const& GetFieldRefFromParameter(Parameter<TFieldType> const& param, bool isDefField = false) {
			return isDefField ? param.GetRef_Default() : param.GetRef_Stat();
		}
		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const Parameter<size_t>* GetParameterByType_s_t(StatType type) const;
		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const Parameter<float>* GetParameterByType_f(StatType type) const;
//
//
// Parameter's definition
//
//

	public:

		static	float	GetAACooldown(float AASpeed) { return (float)1 / AASpeed; }
		
		//HitPoint
		Parameter<size_t> const&	GetMaxHP()			const { return MaxHP; }
		Parameter<size_t> const&	GetHPRegenCount()	const { return RegenHP_Amount; }
		Parameter<float> const&		GetHPRegenTick()	const { return RegenHP_Tick; }
		//Moving
		Parameter<float> const&		GetMovingSpeed()	const { return MovingSpeed; }
		//Attack
		Parameter<size_t> const&	GetAADamage()		const { return AADamage; }
		Parameter<float> const&		GetAASpeed()		const { return AASpeed; }
		float const&				GetAACooldown()		const { return GetAACooldown(AASpeed.GetStat()); }
		Parameter<float> const&		GetAARange()		const { return AARange; }
		//View
		Parameter<float> const&		GetAutoAggrRadius()	const { return AutoAggrRadius; }

		template<typename TFieldType>
		void SetDefaultStat(StatType type, Parameter<TFieldType>& param, TFieldType value) {

			param.Default = value;
			RecalculateStat_t<TFieldType>(type, param);
			DefaultStatChangedEventHan.Execute(type);
		}

		//HitPoint
		void SetMaxHP(size_t hp);
		void SetHPRegenAmount(size_t amount);
		void SetHPRegenTick(float tick);
		//Moving
		void SetMovingSpeed(float speed);
		//Attack
		void SetAADamage(size_t damage);
		void SetAASpeed(float speed);
		void SetAARange(float range);
		//View
		void SetAutoAggrRadius(float radius);


	private:
		//HitPoint
		Parameter<size_t>	MaxHP			= Parameter<size_t>(1);
		Parameter<size_t>	RegenHP_Amount	= Parameter<size_t>(1);		//Amount of restored hp in 1 tick
		Parameter<float>	RegenHP_Tick	= Parameter<float>(1);		//Cooldown between hp's restoring by regeneration
		//Moving
		Parameter<float>	MovingSpeed		= Parameter<float>(1);
		//Attack
		Parameter<size_t>	AADamage		= Parameter<size_t>(0);
		Parameter<float>	AASpeed			= Parameter<float>(0);		//Amount of dealt attack in 1 second
		Parameter<float>	AARange			= Parameter<float>(0);
		//View
		Parameter<float>	AutoAggrRadius	= Parameter<float>(0);
	};
}