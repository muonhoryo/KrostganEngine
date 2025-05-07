#pragma once

#include <IHitPointModule.h>
#include <SFML/System.hpp>
#include <TransformableObj.h>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class IAttackableObj {
	public:
		virtual IHitPointModule& GetHPModule()=0;
		virtual TransformableObj& GetTransform() = 0;
		virtual Vector2f GetClosestPoint(Vector2f dmgDealerPos) const = 0;
		
	protected:
		IAttackableObj(){}
	};
}