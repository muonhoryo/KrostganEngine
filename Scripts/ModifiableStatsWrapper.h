#pragma once

#include <array>
#include <string>
#include <iostream>
#include <IModifiableStatsWrapper.h>
#include <FStreamExts.h>

using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::GameObjects {

	template<typename TStatEnum, size_t STATNAMES_COUNT, const array<pair<TStatEnum,string>,STATNAMES_COUNT>& STATTYPE_NAMES,
		size_t FIELDSCOUNT_F, size_t FIELDSCOUNT_S_T, size_t FIELDSCOUNT_BOOL>
	class ModifiableStatsWrapper : public IModifiableStatsWrapper {

	public:

		ModifiableStatsWrapper(){}

		ModifiableStatsWrapper(const ModifiableStatsWrapper
			<TStatEnum, STATNAMES_COUNT, STATTYPE_NAMES, FIELDSCOUNT_F, FIELDSCOUNT_S_T, FIELDSCOUNT_BOOL> & copy) {

			copy.CopyTo_Internal(*this);
		}
		virtual ~ModifiableStatsWrapper(){

			for (auto mod : ParamModifiers) {
				delete mod;
			}
		}
//
//
// Parameter's getting
//
//

	private:
		struct GetStatTypeCond : public CollectionsExts::Predicate<const pair<TStatEnum, string>&> {

			GetStatTypeCond(const string& name)
				:name(name)
			{}

			virtual bool Condition(const pair<TStatEnum, string>& input) const override {
				return name == input.second;
			}
		private:
			const string& name;
		};

	protected:
		array<Parameter<float>, FIELDSCOUNT_F>		Parameters_f;
		array<Parameter<size_t>, FIELDSCOUNT_S_T>	Parameters_s_t;
		array<bool, FIELDSCOUNT_BOOL>				Parameter_bool;

		const size_t*			_GetFieldRef_s_t(int type, bool isDefField = false) const override{

			auto param = _GetParameterByType_s_t(type);
			if (param == nullptr)
				return nullptr;
			else
				return &GetFieldRefFromParameter(*param, isDefField);
		}
		const float*			_GetFieldRef_f(int type, bool isDefField = false) const override{

			auto param = _GetParameterByType_f(type);
			if (param == nullptr)
				return nullptr;
			else
				return &GetFieldRefFromParameter(*param, isDefField);
		}
		const bool*				_GetFieldRef_bool(int type) const override{

			if (GetFieldType((TStatEnum)type) != ModStatsWrapper_Consts::StatType::t_bool)
				return nullptr;

			int index = GetArrayIndexOfField(type);
			if (index < FIELDSCOUNT_BOOL)
				return &Parameter_bool[index];
			else
				return nullptr;
		}
		const void*				_GetFieldRef(int type, bool isDefField = false) const override {

			ModStatsWrapper_Consts::StatType fieldType = GetFieldType((TStatEnum)type);
			switch (fieldType) {
			case ModStatsWrapper_Consts::StatType::t_size_t:
				return _GetFieldRef_s_t(type, isDefField);
			case ModStatsWrapper_Consts::StatType::t_float:
				return _GetFieldRef_f(type, isDefField);
			case ModStatsWrapper_Consts::StatType::t_bool:
				return _GetFieldRef_bool(type);
			default:
				return nullptr;
			}
		}

		const Parameter<size_t>*	_GetParameterByType_s_t(int type) const override {

			if (GetFieldType((TStatEnum)type) != ModStatsWrapper_Consts::StatType::t_size_t)
				return nullptr;

			int index = GetArrayIndexOfField(type);
			if (index < FIELDSCOUNT_S_T)
				return &Parameters_s_t[index];
			else
				return nullptr;
		}
		const Parameter<float>*		_GetParameterByType_f(int type) const override{

			if (GetFieldType((TStatEnum)type) != ModStatsWrapper_Consts::StatType::t_float)
				return nullptr;

			int index = GetArrayIndexOfField(type);
			if (index < FIELDSCOUNT_F)
				return &Parameters_f[index];
			else
				return nullptr;
		}
		const void*					_GetParameterByType(int type) const override{

			ModStatsWrapper_Consts::StatType fieldType = GetFieldType((TStatEnum)type);
			switch (fieldType) {
			case ModStatsWrapper_Consts::StatType::t_size_t:
				return _GetParameterByType_s_t(type);
			case ModStatsWrapper_Consts::StatType::t_float:
				return _GetParameterByType_f(type);
			default:
				return nullptr;
			}
		}

	public:
		static const string& StatToStr(TStatEnum type) {

			for (auto& pr : STATTYPE_NAMES) {
				if (pr.first == type)
					return pr.second;
			}
			return *new string("");
		}
		static TStatEnum StrToStat(const string& str) {

			auto cond = GetStatTypeCond(str);
			auto type = CollectionsExts::Get_c<const array<pair<TStatEnum, string>, STATNAMES_COUNT>, pair<TStatEnum, string>>(STATTYPE_NAMES, cond);
			return (type == nullptr) ? (TStatEnum)-1 : (type->first);
		}

		static ModStatsWrapper_Consts::StatType	GetFieldType(TStatEnum type) {
			return IModifiableStatsWrapper::GetFieldType((int)type);
		}

		bool WriteParam(Attr& param) override {
			TStatEnum paramType = StrToStat(param.first);
			if ((int)paramType == -1)
				return false;

			ModStatsWrapper_Consts::StatType paramValueType = GetFieldType(paramType);
			switch (paramValueType)
			{
			case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_size_t: {

				auto paramPtr_s_t = Internal_GetParamByType_s_t(paramType);
				paramPtr_s_t->Default = stol(param.second);
				RecalculateStat_t<size_t>(paramType, *paramPtr_s_t);
				return true;
			}
			case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_float: {

				auto paramPtr_f = Internal_GetParamByType_f(paramType);
				paramPtr_f->Default = stof(param.second);
				RecalculateStat_t<float>(paramType, *paramPtr_f);
				return true;
			}
			case KrostganEngine::GameObjects::ModStatsWrapper_Consts::StatType::t_bool: {

				*Internal_GetFieldByType_bool(paramType) = FStreamExts::ParseBool(param.second);
				return true;
			}
			default:
				return false;
			}
		}
		/// <summary>
		/// Copy parameters of this stats to target stats
		/// </summary>
		/// <param name="tocopy"></param>
		virtual void CopyTo(ModifiableStatsWrapper<TStatEnum, STATNAMES_COUNT, STATTYPE_NAMES, FIELDSCOUNT_F, FIELDSCOUNT_S_T, FIELDSCOUNT_BOOL>& toCopy) const {
			CopyTo_Internal(toCopy);
		}
	private:
		void CopyTo_Internal(ModifiableStatsWrapper<TStatEnum, STATNAMES_COUNT, STATTYPE_NAMES, FIELDSCOUNT_F, FIELDSCOUNT_S_T, FIELDSCOUNT_BOOL>& toCopy) const {

			size_t it = 0;

			for (it = 0;it < FIELDSCOUNT_F;++it) {
				toCopy.Parameters_f[it] = Parameter<float>(Parameters_f[it]);
			}
			for (it = 0;it < FIELDSCOUNT_S_T;++it) {
				toCopy.Parameters_s_t[it] = Parameter<size_t>(Parameters_s_t[it]);
			}
			for (it = 0;it < FIELDSCOUNT_BOOL;++it) {
				toCopy.Parameter_bool[it] = Parameter_bool[it];
			}
		}
		
	public:

		const array<Parameter<float>, FIELDSCOUNT_F>& GetParamsArray_f() const {
			return Parameters_f;
		}
		const array<Parameter<size_t>, FIELDSCOUNT_S_T>& GetParamsArray_s_t() const {
			return Parameters_s_t;
		}
		const array<bool, FIELDSCOUNT_BOOL>& GetParamsArray_bool() const {
			return Parameter_bool;
		}

		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const size_t*	GetFieldRef_s_t(TStatEnum type, bool isDefField = false) const {
			return _GetFieldRef_s_t((int)type, isDefField);
		}
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const float*	GetFieldRef_f(TStatEnum type, bool isDefField = false) const {
			return _GetFieldRef_f((int)type, isDefField);
		}
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const bool*		GetFieldRef_bool(TStatEnum type) const {
			return _GetFieldRef_bool((int)type);
		}
		/// <summary>
		/// Return nullptr of field has another type or field don't exists
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const void*		GetFieldRef(TStatEnum type, bool isDefField = false) const {
			return _GetFieldRef((int)type, isDefField);
		}

		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const Parameter<size_t>*	GetParameterByType_s_t(TStatEnum type) const {
			return _GetParameterByType_s_t((int)type);
		}
		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const Parameter<float>*		GetParameterByType_f(TStatEnum type) const {
			return _GetParameterByType_f((int)type);
		}
		/// <summary>
		/// Return nullptr if field has another type of field doesn't exist
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		const void*					GetParameterByType(TStatEnum type) const{
			return _GetParameterByType((int)type);
		}

		template<typename TFieldType>
		static TFieldType const& GetFieldRefFromParameter(Parameter<TFieldType> const& param, bool isDefField = false) {
			return isDefField ? param.GetRef_Default() : param.GetRef_Stat();
		}
		static int GetArrayIndexOfField(int type) {
			return ((type & (int)ModStatsWrapper_Consts::StatType::r_type_mask) >> ModStatsWrapper_Consts::STATTYPE_TYPEDEF_BITSCOUNT) - 1;
		}

	protected:
		Parameter<size_t>*	Internal_GetParamByType_s_t(TStatEnum type) {

			return const_cast<Parameter<size_t>*>(GetParameterByType_s_t(type));
		}
		Parameter<float>*	Internal_GetParamByType_f(TStatEnum type) {

			return const_cast<Parameter<float>*>(GetParameterByType_f(type));
		}
		bool*				Internal_GetFieldByType_bool(TStatEnum type){
			return const_cast<bool*>(GetFieldRef_bool(type));
		}
		void* Internal_GetParamByType(TStatEnum type) {

			return const_cast<void*>(GetParameterByType(type));
		}
		template<typename TFieldType>
		void SetDefaultStat(TStatEnum type, TFieldType value) {

			auto param = static_cast<Parameter<TFieldType>*>(Internal_GetParamByType(type));
			param->Default = value;
			RecalculateStat_t<TFieldType>(type, *param);
			int args = (int)type;
			DefaultStatChangedEventHan.Execute(args);
		}
		template<>
		void SetDefaultStat<bool>(TStatEnum type, bool value) {
			auto param = Internal_GetFieldByType_bool(type);
			*param = value;
			int args = (int)type;
			DefaultStatChangedEventHan.Execute(args);
		}

		void InitializeField_s_t(TStatEnum type, size_t value) {

			auto param = Internal_GetParamByType_s_t(type);
			param->Default = value;
			param->Stat = value;
		}
		void InitializeField_f(TStatEnum type, float value) {
			auto param = Internal_GetParamByType_f(type);
			param->Default = value;
			param->Stat = value;
		}
		void InitializeField_bool(TStatEnum type, bool value) {
			*Internal_GetFieldByType_bool(type) = value;
		}



//
//
// Parameter's modifiers
//
//
	private:
		static inline const ParamModifier_SortFunc<TStatEnum> ParamModsSortFuncInstance = ParamModifier_SortFunc<TStatEnum>();

		vector<const ParamModifier<TStatEnum>*> ParamModifiers;

		void RecalculateStat(TStatEnum type) {
			ModStatsWrapper_Consts::StatType fieldType = GetFieldType(type);

			switch (fieldType) {
			case ModStatsWrapper_Consts::StatType::t_size_t:
				RecalculateStat_t<size_t>(type, *GetParameterByType_s_t(type));
				break;
			case ModStatsWrapper_Consts::StatType::t_float:
				RecalculateStat_t<float>(type, *GetParameterByType_f(type));
				break;
			case ModStatsWrapper_Consts::StatType::t_bool:
				break;
			default:
				cout << "Missing type of field" << endl;
				throw exception("Cant recalculate field");
				return;
			}
			int& args = *new int((int)type);
			StatChangedEventHan.Execute(args);
			delete& args;
		}
		template<typename TFieldType>
		void RecalculateStat_t(TStatEnum type, Parameter<TFieldType> const& param) {

			TFieldType& field = *const_cast<TFieldType*>(&param.GetRef_Stat());
			TFieldType const& defaultField = param.GetRef_Default();

			field = defaultField;

			auto it = ParamModifiers.begin();
			auto itEnd = ParamModifiers.end();
			const ParamModifier<TStatEnum>* mod = nullptr;

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
				const ParamModifier_Sum<TStatEnum, TFieldType>* modSum = nullptr;
				while (it != itEnd) {
					mod = *it;
					if (mod->ModOp != ParamModOpType::PreSum ||
						mod->FieldType != type) {
						break;
					}
					else {
						modSum = static_cast<const ParamModifier_Sum<TStatEnum, TFieldType>*>(mod);
						field += modSum->SumValue;
						++it;
					}
				}
			}

			if (it == itEnd ||
				(mod != nullptr &&
					mod->FieldType != type))
				return;

			//Multiply
			{
				const ParamModifier_Mul<TStatEnum>* modMul = nullptr;
				float mulSumCoef = 1;
				while (it != itEnd) {
					mod = *it;
					if (mod->ModOp != ParamModOpType::Mul ||
						mod->FieldType != type) {
						break;
					}
					else {
						modMul = static_cast<const ParamModifier_Mul<TStatEnum>*>(mod);
						mulSumCoef *= modMul->MulCoef;
						++it;
					}
				}
				field = (TFieldType)((float)field * mulSumCoef);
			}

			if (it == itEnd ||
				(mod != nullptr &&
					mod->FieldType != type))
				return;

			//Post sum
			const ParamModifier_Sum<TStatEnum, TFieldType>* modPostSum = nullptr;
			while (it != itEnd) {
				mod = *it;
				if (mod->FieldType != type) {
					break;
				}
				else {
					modPostSum = static_cast<const ParamModifier_Sum<TStatEnum, TFieldType>*>(mod);
					field += modPostSum->SumValue;
					++it;
				}
			}
		}

	public:
		void AddModifier(const ParamModifier<TStatEnum>& mod) {
			if (StatToStr(mod.FieldType) == "")
				throw exception("Missing field type");

			CollectionsExts::InsertSorted(ParamModifiers, &mod, ParamModsSortFuncInstance);
			RecalculateStat(mod.FieldType);
		}
		void RemoveModifier(const ParamModifier<TStatEnum>& mod) {
			CollectionsExts::Remove(ParamModifiers, &mod);
			RecalculateStat(mod.FieldType);
		}
	};
};