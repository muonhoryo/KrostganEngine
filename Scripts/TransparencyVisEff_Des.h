#pragma once

#include <TransparencyVisEff.h>

using namespace sf;

namespace KrostganEngine::Visual {

	/// <summary>
	/// Destroy owner after fading's end
	/// </summary>
	class TransparencyVisEff_Des final : public TransparencyVisEff {
	public:
		TransparencyVisEff_Des(TransparencyEffectType effectType, float LifeTime, IColoredObject& Owner);
		virtual ~TransparencyVisEff_Des() {}

	protected:
		void Update() override;

	};
}