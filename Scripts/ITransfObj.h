#pragma once

#include <SFML/System.hpp>
#include <watch_ptr.h>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class ITransfObj : public virtual w_ptr_observable {
	public:
		virtual ~ITransfObj(){}

		virtual Vector2f			GetGlobalPosition() const = 0;
		virtual Vector2f			GetLocalPosition() const = 0;
		virtual Vector2f			GetGlobalScale() const = 0;
		virtual Vector2f			GetLocalScale() const = 0;
		virtual Vector2f			GetOrigin() const = 0;
		virtual Vector2f			GetPrevMovStep() const = 0;
		virtual const Transform&	GetTransform() const = 0;
		virtual const Transform&	GetInverseTransform() const = 0;

		virtual void SetGlobalPosition(Vector2f position) = 0;
		virtual void SetLocalPosition(Vector2f position) = 0;
		virtual void SetGlobalScale(Vector2f scale) = 0;
		virtual void SetLocalScale(Vector2f scale) = 0;
		virtual void SetOrigin(Vector2f origin) = 0;

		virtual void Move_Global(Vector2f moveValue) = 0;
		virtual void Move_Local(Vector2f moveValue) = 0;

		//virtual void SetParent(TransformableObj* parent);
		//TransformableObj& GetParent();

	protected:
		ITransfObj(){}
	};
}