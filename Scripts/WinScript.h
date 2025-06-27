#pragma once

#include <SFML/System.hpp>
#include <ICallbackRec_GraphRen.h>
#include <UIUXVisual.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;

namespace KrostganEngine::GameTransitions {
	class WinScript : public ICallbackRec_GraphRen {
	private:
		enum class WinMessageStage : unsigned char {
			Hide,
			Appearing,
			Showing
		};

	public:
		WinScript();

		void RenderGraphic(RenderWindow& window) override;

	private:
		WinMessageStage  Stage = WinMessageStage::Hide;
		Clock LostTimer;
		float MessageAppearingTime;
		float MessageShowingTime;
		float TransitTime;
		float MessageAppearingDeltaTime;
		TextBlock* Message = nullptr;
		TextBlock* Message2 = nullptr;
	};
}