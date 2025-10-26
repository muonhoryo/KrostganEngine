
#include <FadingVisualEffect.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::GameObjects;

FadingVisualEffect::FadingVisualEffect(float FadeTime, IColoredObject& Owner) 
	:VisualEffect(),
	FadeTime		(FadeTime),
	Owner			(Owner),
	DefaultAlpha	((float)Owner.GetColor().a/255){

	HidingTimer.restart();
	Fade();
}

bool FadingVisualEffect::Fade() {

	float time = HidingTimer.getElapsedTime().asSeconds();
	if (time < FadeTime) {

		float transparency = (FadeTime- time) / FadeTime;
		SetOwnerColor(transparency * 255 * DefaultAlpha);
		return false;
	}
	else {

		SetOwnerColor(0);
		return true;
	}
}
void FadingVisualEffect::Reset() {
	
	SetOwnerColor(255 * DefaultAlpha);
	HidingTimer.restart();
}
void FadingVisualEffect::SetDefaultAlpha(float alpha) {
	DefaultAlpha = clamp<float>(alpha, 0, 1);
}
void FadingVisualEffect::SetOwnerColor(Uint8 alpha) {

	Color clr = Owner.GetColor();
	clr = Color(clr.r, clr.g, clr.b, alpha);
	Owner.SetColor(clr);
}