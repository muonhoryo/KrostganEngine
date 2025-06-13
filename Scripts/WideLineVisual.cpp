
#include <PrimitiveVisualShapes.h>
#include <Extensions.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::UI;

WideLineVisual::WideLineVisual(Vector2f Start, Vector2f End, float Width, Color LineColor) 
	:Start(Start),
	End(End),
	Width(Width),
	LineColor(LineColor),
	Vertexes(VertexArray(PrimitiveType::TriangleStrip,4)){

	Rebuild();
	SetColor(LineColor);
}

void WideLineVisual::RenderGraphic(RenderWindow& window) {
	window.draw(Vertexes);
}

void WideLineVisual::SetStart(Vector2f start) {

	Start = start;
	Rebuild();
}

void WideLineVisual::SetEnd(Vector2f end) {

	End = end;
	Rebuild();
}

void WideLineVisual::SetWidth(float width) {

	Width = width;
	Rebuild();
}

void WideLineVisual::SetColor(Color color) {
	
	Vertexes[0].color = color;
	Vertexes[1].color = color;
	Vertexes[2].color = color;
	Vertexes[3].color = color;
}

void WideLineVisual::Rebuild() {

	Vector2f dir = Normalize(End - Start);
	Vector2f n = Vector2f(dir.y * Width, -dir.x * Width);
	Vertexes[0] = Start + n;
	Vertexes[1] = Start - n;
	Vertexes[2] = End + n;
	Vertexes[3] = End - n;
}