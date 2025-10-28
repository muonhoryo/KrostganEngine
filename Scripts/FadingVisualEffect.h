#pragma once

#include <VisualEffectsSystem.h>

using namespace sf;

namespace KrostganEngine::Visual {

	class FadingVisualEffect : public VisualEffect {
	public:
		virtual ~FadingVisualEffect(){}


	protected:
		FadingVisualEffect(float FadeTime, IColoredObject& Owner);

		/// <summary>
		/// Return true if fading is done
		/// </summary>
		/// <returns></returns>
		bool Fade();
		/// <summary>
		/// Set owner color's transparency as default
		/// </summary>
		void Reset();
		void SetDefaultAlpha(float alpha);
		/// <summary>
		/// Return false and destroy the effect if owner doesn't exist
		/// </summary>
		/// <returns></returns>
		bool CheckOwnerExistane();

		Clock									HidingTimer;
		float									FadeTime;
		watch_ptr_handler_wr<IColoredObject>*	Owner;
		float									DefaultAlpha;
		
		void SetOwnerColor(Uint8 alpha);
	};
}