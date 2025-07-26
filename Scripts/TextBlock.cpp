
#include <TextBlock.h>
#include <Engine.h>

using namespace KrostganEngine::UI;
using namespace KrostganEngine;

TextBlock::TextBlock(const string& textStr, unsigned int characterSize)
	:text(*new Text(textStr,ExternalGlobalResources::Get_DefaultFont(), characterSize)) {

	text.setPosition(ScreenPosition);
}
TextBlock::TextBlock()
	:text(*new Text()) {

	text.setPosition(ScreenPosition);
}

void TextBlock::RenderGraphic(RenderWindow& window) {
	text.setPosition(Engine::ScreenPosToGlobalCoord(ScreenPosition));
	window.draw(text);
}