
#include <HighlightVisualEff_MRes.h>

using namespace KrostganEngine::Visual;
using namespace sf;

HighlightVisualEff_MRes::HighlightVisualEff_MRes(float Highlight, IColoredObject& Owner)
	:HighlightVisualEffect(Highlight, Owner) {

}
HighlightVisualEff_MRes::HighlightVisualEff_MRes(IColoredObject& Owner)
	:HighlightVisualEff_MRes(0, Owner) {

}

void HighlightVisualEff_MRes::ResetHighlight(float HighlightTime) {

	this->HighlightTime = HighlightTime;
	InternalResetHighlight();
}
void HighlightVisualEff_MRes::ResetHighlight() {
	if (!IsHighlight) {
		InternalResetHighlight();
	}
}
void HighlightVisualEff_MRes::InternalResetHighlight() {

	Reset();
	IsHighlight = true;
}
void HighlightVisualEff_MRes::SetDefAlpha(float alpha) {
	SetDefaultAlpha(alpha);
}

void HighlightVisualEff_MRes::Update() {
	if (IsHighlight) {
		if (Highlight()) {
			IsHighlight = false;
		}
	}
}