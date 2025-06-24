#pragma once

#include <ICallbackRec_GraphPostRen.h>
#include <SFML/Graphics.hpp>
#include <Engine.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class TextBlock :public ICallbackRec_GraphPostRen {
	public:
		TextBlock(const string& textStr, unsigned int characterSize = 30) 
			:text(*new Text(textStr, *Engine::GetGlobalResources().DefaultFont, characterSize)) {
		}
		TextBlock()
			:text(*new Text()){

			text.setPosition(ScreenPosition);
		}

		void RenderGraphic(RenderWindow& window) override {
			text.setPosition(Engine::ScreenPosToGlobalCoord(ScreenPosition));
			window.draw(text);
		}

		Text& text;
		Vector2f ScreenPosition=Vector2f(0,0);
	};
}