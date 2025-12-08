
#include <GroupSelectionQuad.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace KrostganEngine::UI;

GroupSelectionQuad::GroupSelectionQuad(const Vector2f& StartCorner,const Vector2f& EndCorner) {
	this->StartCorner = StartCorner;
	this->EndCorner = EndCorner;
	RendQuad = &QuadVisPrimitive::InstantiateQuad(StartCorner, EndCorner, Color::Green);
}
GroupSelectionQuad::~GroupSelectionQuad() {
	delete RendQuad;
}

void GroupSelectionQuad::SetEndCorner(const Vector2f& endCorner) {
	EndCorner = endCorner;
	UpdateQuadShape();
}

const Vector2f& GroupSelectionQuad::GetStartCorner() {
	return StartCorner;
}
const Vector2f& GroupSelectionQuad::GetEndCorner() {
	return EndCorner;
}

void GroupSelectionQuad::UpdateQuadShape() {
	RendQuad->SetPointsBy2Corners(StartCorner, EndCorner);
}