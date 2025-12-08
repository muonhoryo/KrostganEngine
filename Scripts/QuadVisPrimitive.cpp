
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <PrimitiveVisualShapes.h>

using namespace sf;
using namespace KrostganEngine::Visual;

QuadVisPrimitive::QuadVisPrimitive(
	Vector2f		lt,
	Vector2f		rt, 
	Vector2f		rb, 
	Vector2f		lb,
	Color			edgeColor,
	std::byte		RendLayer,
	PrimitiveType	quadType,
	sf::Shader*		RenShader)
		:ICallbackRec_GraphRen(RendLayer),
		Shader(RenShader){

	RenStates.shader = Shader;
	Vertexes = VertexArray(quadType, 5);
	SetPoints(lt, rt, rb, lb);
	SetEdgeColor(edgeColor);
}
QuadVisPrimitive::QuadVisPrimitive(
	Vector2f		minCorner,
	Vector2f		maxCorner,
	Color			edgeColor,
	std::byte		RendLayer,
	PrimitiveType	quadType,
	sf::Shader*		RenShader)
		:QuadVisPrimitive(minCorner,Vector2f(maxCorner.x,minCorner.y),maxCorner,Vector2f(minCorner.x,maxCorner.y),
			edgeColor,RendLayer,quadType,RenShader)
{}
FloatRect QuadVisPrimitive::GetBounds() {
	return Vertexes.getBounds();
}
Color QuadVisPrimitive::GetEdgeColor() {
	return Vertexes[0].color;
}

void QuadVisPrimitive::SetPoints(Vector2f lt, Vector2f rt, Vector2f rb, Vector2f lb) {
	Vertexes[0].position = lt;
	Vertexes[1].position = rt;
	Vertexes[2].position = rb;
	Vertexes[3].position = lb;
	Vertexes[4].position = lt;
}
void QuadVisPrimitive::SetPointsBy2Corners(Vector2f corner1, Vector2f corner2) {
	float minX, minY, maxX, maxY;
	if (corner1.x < corner2.x) {
		minX = corner1.x;
		maxX = corner2.x;
	}
	else {
		minX = corner2.x;
		maxX = corner1.x;
	}
	if (corner1.y < corner2.y) {
		minY = corner1.y;
		maxY = corner2.y;
	}
	else {
		minY = corner2.y;
		maxY = corner1.y;
	}
	SetPoints(Vector2f(minX, minY), Vector2f(maxX, minY), Vector2f(maxX, maxY), Vector2f(minX, maxY));
}
void QuadVisPrimitive::SetEdgeColor(Color edgeColor) {
	Vertexes[0].color=edgeColor;
	Vertexes[1].color = edgeColor;
	Vertexes[2].color = edgeColor;
	Vertexes[3].color = edgeColor;
	Vertexes[4].color = edgeColor;
}

void QuadVisPrimitive::RenderGraphicAction(RenderWindow& window) {
	window.draw(Vertexes,RenStates);
}

QuadVisPrimitive& QuadVisPrimitive::InstantiateQuad(Vector2f corner1, Vector2f corner2,Color edgeColor, std::byte RendLayer) {
	float minX, minY, maxX, maxY;
	if (corner1.x < corner2.x) {
		minX = corner1.x;
		maxX = corner2.x;
	}
	else {
		minX = corner2.x;
		maxX = corner1.x;
	}
	if (corner1.y < corner2.y) {
		minY = corner1.y;
		maxY = corner2.y;
	}
	else {
		minY = corner2.y;
		maxY = corner1.y;
	}

	return *new QuadVisPrimitive(
		Vector2f(minX, minY), 
		Vector2f(maxX, minY),
		Vector2f(maxX, maxY), 
		Vector2f(minX, maxY), 
		edgeColor, 
		RendLayer);
}
