#pragma once

#include <FadingVisualEffect.h>

using namespace sf;

namespace KrostganEngine::Visual {

	/// <summary>
	/// Stop changing owner after fading's end. Restart fading after reset.
	/// Reset is manual.
	/// </summary>
	class FadingVisualEff_MRes final : public FadingVisualEffect {
	public:
		FadingVisualEff_MRes(float FadeTime, IColoredObject& Owner);
		FadingVisualEff_MRes(IColoredObject& Owner);

		void ResetFade();
		void ResetFade(float FadeTime);
		void SetDefAlpha(float alpha);

		bool GetIsFadingState() const {
			return IsFading;
		}

	protected:
		void Update() override;

	private:
		bool IsFading = true;

		void InternalResetFade();
	};
}