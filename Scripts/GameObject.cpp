
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Engine.h>
#include <iostream>
#include <Extensions.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

GameObject::GameObject(const Texture& RenTexture, Vector2f RenOffset=Vector2f(0,0), Vector2f Position = Vector2f(0, 0),float Size=1)
	:SpriteRenderer(RenTexture,Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution, RenOffset) {
	this->Size = 1;
	this->Position = Vector2f(0,0);
	SetPosition(Position);
	SetSize(Size);
}
void GameObject::SetPosition(Vector2f position) {
	Position = position;
	SetSpriteInharitedPosition(Position);
}
void GameObject::SetSize(float newSize) {
	Vector2f oldSize = GetSpriteSize();
	Resize(oldSize*newSize/Size);
	Size = newSize;
}
Vector2f GameObject::GetPosition() {
	return Position;
}
float GameObject::GetSize() {
	return Size;
}
