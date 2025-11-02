#pragma once

#include <CollectionsExts.h>

using namespace KrostganEngine;

namespace KrostganEngine::GameObjects {
	template<typename TValueType>
	struct Parameter final {

		Parameter(){}
		Parameter(TValueType Default)
			:Default(Default),
			Stat(Default)
		{}
		/*explicit Parameter(const Parameter<TValueType>& toCopy)
			:Default(toCopy.Default),
			Stat(toCopy.Stat)
		{}*/

		TValueType const& GetRef_Stat() const { return Stat; }
		TValueType const& GetRef_Default() const { return Default; }

		operator TValueType() const {
			return Stat;
		}

		TValueType Stat;
		TValueType Default;
	};

	enum class ParamModOpType : char {
		PreSum,
		Mul,
		PostSum
	};

	template<typename TStatEnumType>
	struct ParamModifier {


		const ParamModOpType ModOp;
		const TStatEnumType FieldType;

	protected:
		ParamModifier(ParamModOpType ModOp, TStatEnumType FieldType)
			:ModOp(ModOp),
			FieldType(FieldType)
		{}
	};
	template<typename TStatEnumType>
	struct ParamModifier_Mul final : public ParamModifier<TStatEnumType> {

		ParamModifier_Mul(TStatEnumType FieldType, float MulCoef)
			:ParamModifier<TStatEnumType>(ParamModOpType::Mul, FieldType),
			MulCoef(MulCoef)
		{}

		float MulCoef;
	};
	template<typename TStatEnumType, typename TValueType>
	struct ParamModifier_Sum final : public ParamModifier<TStatEnumType> {

		ParamModifier_Sum(TStatEnumType FieldType, TValueType SumValue, bool isPostSum)
			:ParamModifier<TStatEnumType>(isPostSum ? ParamModOpType::PostSum : ParamModOpType::PreSum, FieldType),
			SumValue(SumValue)
		{}

		TValueType SumValue;
	};

	template<typename TStatEnumType>
	struct ParamModifier_SortFunc final : CollectionsExts::CompareFunc<const ParamModifier<TStatEnumType>*> {

		bool Compare(const ParamModifier<TStatEnumType>* const& first, const ParamModifier<TStatEnumType>* const& second) const override {

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
}