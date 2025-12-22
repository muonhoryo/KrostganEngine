
#include <TransparencyVisEff_MRes.h>

using namespace KrostganEngine::Visual;
using namespace sf;

TransparencyVisEff_MRes::TransparencyVisEff_MRes(TransparencyEffectType effectType, float EffectTime, IColoredObject& Owner)
	:TransparencyVisEff(effectType, EffectTime, Owner) {

}
TransparencyVisEff_MRes::TransparencyVisEff_MRes(TransparencyEffectType effectType, IColoredObject& Owner)
	:TransparencyVisEff(effectType, 0, Owner) {

}

void TransparencyVisEff_MRes::ResetEffect(float EffTime) {

	this->EffTime= EffTime;
	InternalResetEffect();
}
void TransparencyVisEff_MRes::ResetEffect() {
	
	InternalResetEffect();
}
void TransparencyVisEff_MRes::InternalResetEffect() {

	Reset();
	IsEffUpdate= true;
}
void TransparencyVisEff_MRes::SetDefAlpha(float alpha) {
	SetDefaultAlpha(alpha);
}

void TransparencyVisEff_MRes::Update() {
	if (IsEffUpdate) {
		if (UpdateEff()) {
			IsEffUpdate = false;
		}
	}
}