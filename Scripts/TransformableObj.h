#pragma once

#include <SFML/System.hpp>
#include <watch_ptr.h>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class TransformableObj : public virtual w_ptr_observable{
	public:
		~TransformableObj(){}

		Vector2f GetPosition() const;
		float GetScale()const ;

		virtual void SetPosition(Vector2f position);
		virtual void SetScale(float scale);

		void Move(Vector2f moveValue);

	protected:
		TransformableObj(Vector2f Position, float Scale);
		TransformableObj();

	private:
		Vector2f Position;
		float Scale;
	};
}