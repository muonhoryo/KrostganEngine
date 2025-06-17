
#include <SingleSprite.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Visual;

SingleSprite::SingleSprite(const Texture& RenTexture, float maxSpriteSize,Vector2f RenOffset, Vector2f Position, float Scale, Color SprColor)
	:TransformableObj(Position,1),
	SpriteRenderer(RenTexture, maxSpriteSize, RenOffset,SprColor){
	SetPosition(Position);
	SetScale(Scale);
}

void SingleSprite::SetPosition(Vector2f position) {
	TransformableObj::SetPosition(position);
	SetSpriteInharitedPosition(GetPosition());
}
void SingleSprite::SetScale(float scale) {
	Vector2f oldSize = GetSpriteSize();
	float mult = scale / GetScale();
	ResizeSprite(Vector2f(oldSize.x*mult,oldSize.y*mult));
	TransformableObj::SetScale(scale);
}