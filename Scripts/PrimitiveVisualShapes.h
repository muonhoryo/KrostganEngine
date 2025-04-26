#pragma once

//#include <EngineCore.h>
#include <ICallbackRec_GraphRen.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class QuadVisPrimitive :public ICallbackRec_GraphRen {
	public:
		QuadVisPrimitive(Vector2f lt, Vector2f rt, Vector2f rb, Vector2f lb,
			Color edgeColor);

		FloatRect GetBounds();
		Color GetEdgeColor();

		void SetPoints(Vector2f lt, Vector2f rt, Vector2f rb, Vector2f lb);
		void SetPointsBy2Corners(Vector2f corner1, Vector2f corner2);
		void SetEdgeColor(Color edgeColor);

		void RenderGraphic(RenderWindow& window) override;

		static QuadVisPrimitive& InstanceQuad(Vector2f corner1, Vector2f corner2, Color edgeColor);
	private:
		VertexArray Vertexes;
	};

	class CircleVisPrimitive : public ICallbackRec_GraphRen {
	public:
		CircleVisPrimitive(Vector2f center, float radius,Color edgeColor,size_t pointsCount);

		Vector2f GetCenter();
		float GetRadius();
		Color GetEdgeColor();
		size_t GetPointsCount();

		void SetCenter(Vector2f center);
		void SetRadius(float radius);
		void SetEdgeColor(Color color);
		void SetPointsCount(size_t count);

		void RenderGraphic(RenderWindow& window) override;

	private:
		CircleShape CirShape;
	};
}