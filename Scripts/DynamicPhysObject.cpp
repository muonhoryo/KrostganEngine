
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
		cout << "Resolving collision" << endl;
		size_t resolCount = 0;
		size_t max = Engine::GetGlobalConsts().Physics_MaxCollsResolvCount;
		Vector2f resolvPnt = Vector2f(0, 0);
		for (auto coll : colls) {
			if (coll == this)
				continue;

			if (!TryGetResolNormal(coll->GetCollider(),MoveDirection, &resolvPnt))
				throw exception("Cannot get resolving normal");

			SetPosition(resolvPnt);
			++resolCount;
			if (resolCount >= max)
				break;
		}
		HasMoved = false;
	}
}