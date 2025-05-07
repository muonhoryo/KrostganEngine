#pragma once

#include <IPhysicalObject.h>
#include <EngineWorkCycleModule.h>
#include <vector>
#include <PhysicsLayer.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Physics {
	class PhysicsEngine: public EngineCallbackHandler<IPhysicalObject>
	{
	public:
		PhysicsEngine();

		vector<IPhysicalObject*> OverlapAABB_All(Vector2f min, Vector2f max, PhysicsLayer layer=PhysicsLayer::All);

		IPhysicalObject* PointCast(Vector2f globalPos, PhysicsLayer layer = PhysicsLayer::All);
	};
}


