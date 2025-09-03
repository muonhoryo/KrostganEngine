#pragma once

#include <VisualEffectsSystem.h>

using namespace sf;

namespace KrostganEngine::Visual {

	class HighlightVisualEffect : public VisualEffect {
	public:
		virtual ~HighlightVisualEffect() {}


	protected:
		HighlightVisualEffect(float HighLightTime, IColoredObject& Owner);

		/// <summary>
		/// Return true if fading is done
		/// </summary>
		/// <returns></returns>
		bool Highlight();
		/// <summary>
		/// Set owner color's transparency as default
		/// </summary>
		void Reset();
		void SetDefaultAlpha(float alpha);

		Clock			Timer;
		float			HighlightTime;
		IColoredObject& Owner;
		float			DefaultAlpha;

		void SetOwnerColor(Uint8 alpha);
	};
}