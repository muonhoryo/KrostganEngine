
#include <SquareScaleSprite.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Visual;

SquareScaleSprite::SquareScaleSprite(
	const Texture&	RenTexture, 
	float			maxSpriteSize,
	Vector2f		GlobalPosition,
	float			LocalScale, 
	Color			SprColor,
	Shader*			RendShader)
	
	:SpriteRenderer(RenTexture,maxSpriteSize, GlobalPosition,Vector2f(LocalScale,LocalScale), SprColor, RendShader)
{}

SquareScaleSprite::SquareScaleSprite(
	const Texture& RenTexture,
	WorldTransfObj& Parent,
	float				maxSpriteSize,
	Vector2f			GlobalPosition,
	float				LocalScale,
	Color				SprColor ,
	Shader*				RendShader)

	:SpriteRenderer(RenTexture,Parent, maxSpriteSize , GlobalPosition,Vector2f(LocalScale, LocalScale),SprColor,RendShader)
{}

void SquareScaleSprite::SetGlobalScale(Vector2f scale) {

	float scl = GetScale_Inter(scale);
	SpriteRenderer::SetGlobalScale(Vector2f(scl, scl));
}
void SquareScaleSprite::SetLocalScale(Vector2f scale) {

	float scl = GetScale_Inter(scale);
	SpriteRenderer::SetLocalScale(Vector2f(scl, scl));
}
float SquareScaleSprite::GetScale_Inter(const Vector2f& scale) const {
	return min(scale.x, scale.y);
}