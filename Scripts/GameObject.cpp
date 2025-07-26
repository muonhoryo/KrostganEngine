
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <Extensions.h>
#include <Engine.h>
#include <TransformableObj.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

GameObject::GameObject(
	const Texture&	RenTexture, 
	Vector2f		RenOffset, 
	Vector2f		Position , 
	float			Size ,
	Color			SprColor,
	Shader*			RenShader)
	:SingleSprite(
		RenTexture, 
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution, 
		RenOffset, 
		Position, 
		Size,
		SprColor,
		RenShader),
	DynamicPhysObject(), 
	TransformableObj(Position,Size) {}

void GameObject::SetPosition(Vector2f position) {
	DynamicPhysObject::SetPosition(position);
	SingleSprite::SetPosition(position);
}
void GameObject::SetScale(float scale) {
	SingleSprite::SetScale(scale);
}