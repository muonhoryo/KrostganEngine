#pragma once

#include <SFML/System.hpp>
#include <watch_ptr.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#define DEFAULT_SCALE		Vector2f(1,1)
#define DEFAULT_POSITION	Vector2f(0,0)
#define DEFAULT_ORIGIN		Vector2f(0,0)


namespace KrostganEngine::Core {
	class ITransformableObj : public virtual w_ptr_observable {

	public:
		virtual ~ITransformableObj() {}

		virtual Vector2f			GetGlobalPosition() const = 0;
		virtual Vector2f			GetGlobalScale() const = 0;
		virtual Vector2f			GetOrigin() const = 0;
		virtual const Transform&	GetTransform() const = 0;
		virtual const Transform&	GetInverseTransform() const = 0;

		virtual Vector2f				GetLocalPosition() const = 0;
		virtual Vector2f				GetLocalScale() const = 0;

		virtual void SetGlobalPosition(Vector2f position) = 0;
		virtual void SetLocalPosition(Vector2f position) = 0;
		virtual void SetGlobalScale(Vector2f scale) = 0;
		virtual void SetLocalScale(Vector2f scale) = 0;
		virtual void SetOrigin(Vector2f origin) = 0;

		void Move_Global(Vector2f moveValue) {
			Vector2f nextPos = GetGlobalPosition() + moveValue;
			SetGlobalPosition(nextPos);
		}
		void Move_Local(Vector2f moveValue) {
			Vector2f nextPos = GetLocalPosition() + moveValue;
			SetLocalPosition(nextPos);
		}

		static inline const Vector2i		NULL_POS = Vector2i(INT_MIN, INT_MIN);

	protected:
		ITransformableObj() {}
	};
}