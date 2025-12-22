
#include <TransparencyVisEff_Des.h>

using namespace sf;
using namespace KrostganEngine::Visual;

TransparencyVisEff_Des::TransparencyVisEff_Des(TransparencyEffectType effectType, float LifeTime, IColoredObject& Owner)
	:TransparencyVisEff(effectType, LifeTime, Owner) {

}

void TransparencyVisEff_Des::Update() {

	if (UpdateEff()) {

		delete Owner->GetPtr_t();
		delete this;
	}
}