#pragma once

#include <FadingVisualEffect.h>

using namespace sf;

namespace KrostganEngine::Visual {

	/// <summary>
	/// Destroy owner after fading's end
	/// </summary>
	class FadingVisualEff_Des final : public FadingVisualEffect{
	public:
		FadingVisualEff_Des(float LifeTime, IColoredObject& Owner);

	protected:
		void Update() override;

	};
}