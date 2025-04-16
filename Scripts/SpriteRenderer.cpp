
#include <EngineCallbacks.h>
#include <SpriteRenderer.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace KrostganEngine::GameObjects;

SpriteRenderer::SpriteRenderer(const Texture& RenTexture,Vector2f Offset=Vector2f(0,0)) :ICallbackRec_GraphRen(){
	RenSprite.setTexture(RenTexture);
	this->Offset = Offset;
}
void SpriteRenderer::RenderGraphic(RenderWindow& window) {
	window.draw(RenSprite);
}
const Texture& SpriteRenderer::GetRenTexture() {
	return *RenSprite.getTexture();
}
Vector2f SpriteRenderer::GetOffset() {
	return Offset;
}
Vector2f SpriteRenderer::GetGlobalPosition() {
	return RenSprite.getPosition();
}
Vector2f SpriteRenderer::GetInharitedPosition() {
	return  GetGlobalPosition()-GetOffset();
}
void SpriteRenderer::SetOffset(Vector2f offset) {
	Vector2f inharPos = GetInharitedPosition();
	Offset = offset;
	SetSpriteInharitedPosition(inharPos);
}

void SpriteRenderer::SetSpriteInharitedPosition(Vector2f position) {
	RenSprite.setPosition(position + GetOffset());
}