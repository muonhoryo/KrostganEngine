#pragma once

#include <TransparencyVisEff.h>

using namespace sf;

namespace KrostganEngine::Visual {

	/// <summary>
	/// Stop changing owner after highlighting's end. Restart highlighting after reset.
	/// Reset is manual.
	/// </summary>
	class TransparencyVisEff_MRes final : public TransparencyVisEff {
	public:
		TransparencyVisEff_MRes(TransparencyEffectType effectType, float EffectTime, IColoredObject& Owner);
		TransparencyVisEff_MRes(TransparencyEffectType effectType, IColoredObject& Owner);

		void ResetEffect();
		void ResetEffect(float EffectTime);
		void SetDefAlpha(float alpha);

		bool GetIsEffUpdateState() const {
			return IsEffUpdate;
		}

	protected:
		void Update() override;

	private:
		bool IsEffUpdate = true;

		void InternalResetEffect();
	};
}