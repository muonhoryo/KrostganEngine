
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace KrostganEngine::GameObjects;

GameObject::GameObject(const Texture& RenTexture, Vector2f RenOffset=Vector2f(0,0), Vector2f Position = Vector2f(0, 0))
	:SpriteRenderer(RenTexture,RenOffset){
	SetPosition(Position);
}
void GameObject::SetPosition(Vector2f position) {
	Position = position;
	SetSpriteInharitedPosition(Position);
}
Vector2f GameObject::GetPosition() {
	return Position;
}
