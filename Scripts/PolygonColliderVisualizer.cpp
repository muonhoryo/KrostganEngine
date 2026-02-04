
#include <PolygonColliderVisualizer.h>

using namespace KrostganEngine::Debug;

PolygonColliderVisualizer::PolygonColliderVisualizer(PolygonCollShape& Owner)
	:Owner(Owner),
		LinesVisPrimitive(Init_GetPoints(Owner), Color::Red, std::byte(128)) {

}
PolygonColliderVisualizer::~PolygonColliderVisualizer() {

}
vector<Vector2f>& PolygonColliderVisualizer::Init_GetPoints(PolygonCollShape& owner) {

	auto& points = owner.GetPoints();
	auto& vec = *new vector<Vector2f>(points.size() + 1);
	for (int i = 0;i < points.size();++i) {
		vec[i] = points[i];
	}
	vec[points.size()] = points[0];
	return vec;
}

void PolygonColliderVisualizer::RenderGraphicAction(RenderWindow& window) {
	LinesVisPrimitive::RenderGraphicAction(window);
}