
#include <EngineCore.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

IPhysicalObject::IPhysicalObject() {
	IPhysicalObject* ref = this;
	Engine::GetPhysicsEngine().Add(ref);
}
IPhysicalObject::~IPhysicalObject() {
	IPhysicalObject* ref = this;
	Engine::GetPhysicsEngine().Remove(ref);
}