#pragma once

#include <SFML/System.hpp>
#include <ICallbackRec_GraphRen.h>
#include <CoreVisual_UI.h>
#include <UIUXVisual.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;

namespace KrostganEngine::GameTransitions {
	class LoseScript : public ICallbackRec_GraphRen{
	private:
		enum class LoseMessageStage : unsigned char {
			Hide,
			Appearing,
			Showing
		};

	public:
		LoseScript();

		void RenderGraphic(RenderWindow& window) override;

	private:
		LoseMessageStage Stage = LoseMessageStage::Hide;
		Clock LostTimer;
		float MessageAppearingTime;
		float MessageShowingTime;
		float TransitTime;
		float MessageAppearingDeltaTime;
	};
}