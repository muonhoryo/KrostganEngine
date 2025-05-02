
#include <PrimitiveVisualShapes.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::UI;



LinesVisPrimitive::LinesVisPrimitive(vector<Vector2f>& pointsCoord, Color edgeColor) {
	size_t pointsCount = pointsCoord.size();
	if (pointsCount== 0) {
		throw exception("Lines primitive cannot be created without points");
	}
	Vertexes = VertexArray(PrimitiveType::Lines, pointsCount);
	for (int i = 0;i < pointsCount;i++) {
		Vertexes[i].position = pointsCoord[i];
		Vertexes[i].color = edgeColor;
	}
}

Color LinesVisPrimitive::GetEdgeColor() {
	return Vertexes[0].color;
}
size_t LinesVisPrimitive::GetPointsCount() {
	return Vertexes.getVertexCount();
}

void LinesVisPrimitive::AddPoint(Vector2f point) {
	size_t newSize= GetPointsCount() + 1;
	Vertexes.resize(newSize);
	Vertexes[newSize - 1].position = point;
	Vertexes[newSize - 1].color = Vertexes[0].color;
}
void LinesVisPrimitive::RemovePointAt(size_t index) {
	size_t count = GetPointsCount();
	if (index >= count)
		throw exception("Index out of range");
	if (count<=1)
		throw exception("Lines primitive is already empty.");
	size_t overWCount = count - index - 1;
	--count;
	if (overWCount > 0) {
		vector<Vector2f> points = vector<Vector2f>(overWCount);
		for (size_t i = index+1;i < count+1;i++) {
			points.push_back(Vertexes[i].position);
		}
		Vertexes.resize(count);
		for (size_t i = index, j = 0;i < count;i++) {
			Vertexes[i].position = points[j];
		}
	}
	else {
		Vertexes.resize(count);
	}
}
void LinesVisPrimitive::ReduceSize(size_t newCount) {
	if (newCount < 1||newCount>GetPointsCount())
		throw "Count out of range";
	if (newCount == GetPointsCount())
		return;
	Vertexes.resize(newCount);
}
void LinesVisPrimitive::SetEdgeColor(Color color) {
	for (int i = 0;i < GetPointsCount();i++) {
		Vertexes[i].color = color;
	}
}
void LinesVisPrimitive::SetPointPosition(Vector2f newPos, size_t pointIndex) {
	if (pointIndex >= GetPointsCount())
		throw exception("Index out of range");
	Vertexes[pointIndex].position = newPos;
}

void LinesVisPrimitive::RenderGraphic(RenderWindow& window) {
	window.draw(Vertexes);
}