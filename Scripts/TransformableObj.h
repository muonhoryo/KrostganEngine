#pragma once

#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class TransformableObj {
	public:
		~TransformableObj(){}

		Vector2f GetPosition();
		float GetScale();

		virtual void SetPosition(Vector2f position);
		virtual void SetScale(float scale);

	protected:
		TransformableObj(Vector2f Position, float Scale);

	private:
		Vector2f Position;
		float Scale;
	};
}