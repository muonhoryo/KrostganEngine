
#include <_EngineCore.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

IPhysicalObject::IPhysicalObject() {
	Engine::GetPhysicsEngine().Add(*this);
}
IPhysicalObject::~IPhysicalObject() {
	IPhysicalObject& ref = *this;
	Engine::GetPhysicsEngine().Remove(*this);
}