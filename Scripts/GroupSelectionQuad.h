#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <PrimitiveVisualShapes.h>

using namespace sf;
using namespace Visual;

namespace KrostganEngine::UI {
	class GroupSelectionQuad  {
	public:
		GroupSelectionQuad(const Vector2f& StartCorner,const Vector2f& EndCorner);
		~GroupSelectionQuad();

		void SetEndCorner(const Vector2f& corner);

		const Vector2f& GetStartCorner();
		const Vector2f& GetEndCorner();

	private:
		Vector2f StartCorner;
		Vector2f EndCorner;
		QuadVisPrimitive* RendQuad;

		void UpdateQuadShape();
	};
}