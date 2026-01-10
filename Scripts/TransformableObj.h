#pragma once

#pragma warning( disable : 4250 )

#define _USE_MATH_DEFINES

#include <math.h>

#include <ITransformableObj.h>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	class TransformableObj : public virtual ITransformableObj{

	private:
		Transformable& Owner;

	public:
		virtual ~TransformableObj(){
			delete& Owner;
		}

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
		float GetGlobalRotation() const override final {
			return Owner.getRotation();
		}

	protected:
		TransformableObj(Transformable& Owner)
			:Owner(Owner){}

		Transformable& GetOwner_inter() {
			return Owner;
		}
	};
}