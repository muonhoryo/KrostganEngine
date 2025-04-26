
#include <SingleSprite.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::UI;

SingleSprite::SingleSprite(const Texture& RenTexture, float maxSpriteSize,Vector2f RenOffset = Vector2f(0, 0), Vector2f Position = Vector2f(0, 0), float Scale = 1)
	:TransformableObj(Position,1),
	SpriteRenderer(RenTexture, maxSpriteSize, RenOffset){
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