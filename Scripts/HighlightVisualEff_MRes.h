#pragma once

#include <HighlightVisualEffect.h>

using namespace sf;

namespace KrostganEngine::Visual {

	/// <summary>
	/// Stop changing owner after highlighting's end. Restart highlighting after reset.
	/// Reset is manual.
	/// </summary>
	class HighlightVisualEff_MRes final : public HighlightVisualEffect{
	public:
		HighlightVisualEff_MRes(float HighlightTime, IColoredObject& Owner);
		HighlightVisualEff_MRes(IColoredObject& Owner);

		void ResetHighlight();
		void ResetHighlight(float FadeTime);
		void SetDefAlpha(float alpha);

		bool GetIsHighlightState() const {
			return IsHighlight;
		}

	protected:
		void Update() override;

	private:
		bool IsHighlight = true;

		void InternalResetHighlight();
	};
}