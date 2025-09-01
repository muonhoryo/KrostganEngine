
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <PrimitiveVisualShapes.h>
#include <iostream>
#include <Extensions.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::UI;

CircleVisPrimitive::CircleVisPrimitive(
	Vector2f	center, 
	float		radius, 
	Color		edgeColor,
	size_t		pointsCount,
	char		RendLayer)
		:ICallbackRec_GraphPostRen(RendLayer)
{
	CirShape = CircleShape(radius, pointsCount);
	CirShape.setOrigin(Vector2f(radius,radius));
	CirShape.setFillColor(Color::Transparent);
	CirShape.setOutlineThickness(1);
	SetCenter(center);
	SetEdgeColor(edgeColor);

	cout << "Create circle at position: " + ToString<float>(GetCenter())<<endl;
}

Vector2f CircleVisPrimitive::GetCenter() {
	return CirShape.getPosition();
}
float CircleVisPrimitive::GetRadius() {
	return CirShape.getRadius();
}
Color CircleVisPrimitive::GetEdgeColor() {
	return CirShape.getOutlineColor();
}
size_t CircleVisPrimitive::GetPointsCount() {
	return CirShape.getPointCount();
}

void CircleVisPrimitive::SetCenter(Vector2f center) {
	CirShape.setPosition(center);
}
void CircleVisPrimitive::SetRadius(float radius) {
	CirShape.setRadius(radius);
	CirShape.setOrigin(radius, radius);
}
void CircleVisPrimitive::SetEdgeColor(Color color) {
	CirShape.setOutlineColor(color);
}
void CircleVisPrimitive::SetPointsCount(size_t count) {
	CirShape.setPointCount(count);
}

void CircleVisPrimitive::RenderGraphic(RenderWindow& window) {
	window.draw(CirShape);
}