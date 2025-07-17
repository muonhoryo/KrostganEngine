#pragma once

#include <ICallbackRec_GraphPostRen.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class TextBlock :public ICallbackRec_GraphPostRen {
	public:
		TextBlock(const string& textStr, unsigned int characterSize = 30);
		TextBlock();

		void RenderGraphic(RenderWindow& window) override;

		Text& text;
		Vector2f ScreenPosition=Vector2f(0,0);
	};
}