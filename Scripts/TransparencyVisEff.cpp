
#include <TransparencyVisEff.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::GameObjects;

TransparencyVisEff::TransparencyVisEff(TransparencyEffectType effectType, float EffTime, IColoredObject& Owner)
	:VisualEffect(),
	EffTime(EffTime),
	DefaultAlpha((float)Owner.GetColor().a / 255),
	GetTransparencyFunc(GetTranspFuncByEnum(effectType)){

	auto& ptr = Owner.GetPtr();
	this->Owner = new watch_ptr_handler_wr<IColoredObject>(ptr);
	delete& ptr;
	EffTimer.restart();
	UpdateEff();
}

bool TransparencyVisEff::UpdateEff() {

	if (!CheckOwnerExistane())
		return true;

	float time = EffTimer.getElapsedTime().asSeconds();
	float transparency;
	bool result = time >= EffTime;
	if (!result) {

		transparency = (this->*GetTransparencyFunc)(time);
	}
	else {

		transparency = (this->*GetTransparencyFunc)(EffTime);
	}
	SetOwnerColor((Uint8)(transparency * 255 * DefaultAlpha));
	return result;
}
void TransparencyVisEff::Reset() {

	if (!CheckOwnerExistane())
		return;

	SetOwnerColor((this->*GetTransparencyFunc)(0) * 255 * DefaultAlpha);
	EffTimer.restart();
}
void TransparencyVisEff::SetDefaultAlpha(float alpha) {
	if (!CheckOwnerExistane())
		return;

	DefaultAlpha = clamp<float>(alpha, 0, 1);
}
void TransparencyVisEff::SetOwnerColor(Uint8 alpha) {

	if (!CheckOwnerExistane())
		return;

	auto ptr = Owner->GetPtr_t();

	Color clr = ptr->GetColor();
	clr = Color(clr.r, clr.g, clr.b, alpha);
	ptr->SetColor(clr);
}
bool TransparencyVisEff::CheckOwnerExistane() {
	if (Owner->GetPtr_t() == nullptr) {
		delete this;
		return false;
	}
	else
		return true;
}