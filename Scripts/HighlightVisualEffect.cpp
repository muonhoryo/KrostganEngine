
#include <HighlightVisualEffect.h>
#include <Engine.h>
#include <cmath>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::GameObjects;

HighlightVisualEffect::HighlightVisualEffect(float HighlightTime, IColoredObject& Owner)
	:VisualEffect(),
	HighlightTime(HighlightTime),
	Owner(Owner),
	DefaultAlpha((float)Owner.GetColor().a / 255) {

	Timer.restart();
}

bool HighlightVisualEffect::Highlight() {

	float time = Timer.getElapsedTime().asSeconds();
	if (time < HighlightTime) {

		float value =   time/ HighlightTime;
		SetOwnerColor( (Uint8)(lerp(DefaultAlpha,1,value) * (double)255));
		return false;
	}
	else {

		SetOwnerColor(255);
		return true;
	}
}
void HighlightVisualEffect::Reset() {

	SetOwnerColor(255 * DefaultAlpha);
	Timer.restart();
}
void HighlightVisualEffect::SetDefaultAlpha(float alpha) {
	DefaultAlpha = clamp<float>(alpha, 0, 1);
}
void HighlightVisualEffect::SetOwnerColor(Uint8 alpha) {

	Color clr = Owner.GetColor();
	clr = Color(clr.r, clr.g, clr.b, alpha);
	Owner.SetColor(clr);
}