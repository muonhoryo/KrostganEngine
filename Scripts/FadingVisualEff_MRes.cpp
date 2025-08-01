
#include <FadingVisualEff_MRes.h>

using namespace KrostganEngine::Visual;
using namespace sf;

FadingVisualEff_MRes::FadingVisualEff_MRes(float FadeTime, IColoredObject& Owner) 
	:FadingVisualEffect(FadeTime,Owner){

}
FadingVisualEff_MRes::FadingVisualEff_MRes(IColoredObject& Owner)
	:FadingVisualEff_MRes(0,Owner){

}

void FadingVisualEff_MRes::ResetFade(float FadeTime) {

	this->FadeTime = FadeTime;
	InternalResetFade();
}
void FadingVisualEff_MRes::ResetFade() {
	if (!IsFading) {
		InternalResetFade();
	}
}
void FadingVisualEff_MRes::InternalResetFade() {

	Reset();
	IsFading = true;
}
void FadingVisualEff_MRes::SetDefAlpha(float alpha) {
	SetDefaultAlpha(alpha);
}

void FadingVisualEff_MRes::Update() {
	if (IsFading) {
		if (Fade()) {
			IsFading = false;
		}
	}
}