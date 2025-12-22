
#include <TransparencyVisEff.h>

using namespace KrostganEngine::Visual;

float(TransparencyVisEff::* TransparencyVisEff::GetTranspFuncByEnum(TransparencyEffectType type))(float) const{

	TransparencyEffectType progressType = 
		(TransparencyEffectType)((unsigned int)type & (unsigned int)TransparencyEffectType::ProgressTypeMask);
	TransparencyEffectType funcType =
		(TransparencyEffectType)((unsigned int)type & (unsigned int)TransparencyEffectType::FuncTypeMask);
	if (progressType == TransparencyEffectType::Fading) {

		switch (funcType)
		{
		case TransparencyEffectType::Linear:
			return &TransparencyVisEff::GetTransparency_Fading_Linear;
		default:
			throw exception("Uknown type of transparency effect func");
		}
	}
	else {

		switch (funcType)
		{
		case TransparencyEffectType::Linear:
			return &TransparencyVisEff::GetTransparency_Highlight_Linear;
		default:
			throw exception("Uknown type of transparency effect func");
		}
	}
}

float TransparencyVisEff::GetTransparency_Fading_Linear(float time) const {

	return (EffTime- time) / EffTime;
}

float TransparencyVisEff::GetTransparency_Highlight_Linear(float time) const {

	return time / EffTime;
}