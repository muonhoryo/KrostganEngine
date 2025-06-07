
#include <DynamicPhysObject.h>
#include <Engine.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

DynamicPhysObject::~DynamicPhysObject() {
}

DynamicPhysObject::DynamicPhysObject() : IPhysicalObject() {
}

void DynamicPhysObject::SetPosition(Vector2f position) {
	Vector2f oldPos = GetPosition();
	TransformableObj::SetPosition(position);
	MoveDirection = GetPosition() - oldPos;
	HasMoved = true;
}

void DynamicPhysObject::Update(CallbackRecArgs_LUpd args) {

	if (HasMoved) {
		auto colls = OverlapAll();

		if (colls.size() == 0) {
			HasMoved = false;
			return;
		}
		size_t resolCount = 0;
		size_t max = Engine::GetGlobalConsts().Physics_MaxCollsResolvCount;
		for (auto coll : colls) {
			if (coll == this)
				continue;

			SetPosition(GetResolvingPnt(coll->GetCollider(), MoveDirection));
			++resolCount;
			if (resolCount >= max)
				break;
		}
		HasMoved = false;
	}
}