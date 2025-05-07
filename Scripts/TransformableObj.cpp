
#include <TransformableObj.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::GameObjects;

TransformableObj::TransformableObj(Vector2f Position=Vector2f(0,0), float Scale=1) {
	this->Position = Vector2f(0,0);
	this->Scale = 1;
	SetPosition(Position);
	SetScale(Scale);
}

Vector2f TransformableObj::GetPosition() const {
	return Position;
}
float TransformableObj::GetScale() const{
	return Scale;
}

void TransformableObj::SetPosition(Vector2f position) {
	Position = position;
}
void TransformableObj::SetScale(float scale) {
	Scale = scale;
}
void TransformableObj::Move(Vector2f movValue) {
	Vector2f nextPos = GetPosition() + movValue;
	SetPosition(nextPos);
}