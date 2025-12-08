
#include <FadingVisualEffect.h>
#include <Engine.h>

#include <iostream>
using namespace std;

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::GameObjects;

FadingVisualEffect::FadingVisualEffect(float FadeTime, IColoredObject& Owner) 
	:VisualEffect(),
	FadeTime		(FadeTime),
	DefaultAlpha	((float)Owner.GetColor().a/255){

	auto& ptr= Owner.GetPtr();
	this->Owner = new watch_ptr_handler_wr<IColoredObject>(ptr);
	delete& ptr;
	HidingTimer.restart();
	Fade();
}

bool FadingVisualEffect::Fade() {

	if (!CheckOwnerExistane())
		return true;

	float time = HidingTimer.getElapsedTime().asSeconds();
	if (time < FadeTime) {

		float transparency = (FadeTime- time) / FadeTime;
		SetOwnerColor((Uint8)(transparency * 255 * DefaultAlpha));
		return false;
	}
	else {

		SetOwnerColor(0);
		return true;
	}
}
void FadingVisualEffect::Reset() {

	if (!CheckOwnerExistane())
		return;

	SetOwnerColor(255 * DefaultAlpha);
	HidingTimer.restart();
}
void FadingVisualEffect::SetDefaultAlpha(float alpha) {
	if (!CheckOwnerExistane())
		return;

	DefaultAlpha = clamp<float>(alpha, 0, 1);
}
void FadingVisualEffect::SetOwnerColor(Uint8 alpha) {

	if (!CheckOwnerExistane())
		return;

	auto ptr = Owner->GetPtr_t();

	Color clr = ptr->GetColor();
	clr = Color(clr.r, clr.g, clr.b, alpha);
	ptr->SetColor(clr);
}
bool FadingVisualEffect::CheckOwnerExistane() {
	if (Owner->GetPtr_t() == nullptr) {
		delete this;
		return false;
	}
	else
		return true;
}