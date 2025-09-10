#pragma once

#include <ITransformableObj.h>

using namespace sf;

namespace KrostganEngine::Core {
	class TransformableObj : public virtual ITransformableObj{

	private:
		Transformable& Owner;

	public:
		virtual ~TransformableObj(){}

		Vector2f			GetGlobalPosition() const override final {
			return Owner.getPosition();
		}
		Vector2f			GetGlobalScale() const override final {
			return Owner.getScale();
		}
		Vector2f			GetOrigin() const override final {
			return Owner.getOrigin();
		}
		const Transform&	GetTransform() const override final {
			return Owner.getTransform();
		}
		const Transform&	GetInverseTransform() const override final {
			return Owner.getInverseTransform();
		}

	protected:
		TransformableObj(Transformable& Owner)
			:Owner(Owner){}

		Transformable& GetOwner_inter() {
			return Owner;
		}
	};
}