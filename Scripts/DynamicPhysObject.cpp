
#include <DynamicPhysObject.h>
#include <Engine.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

DynamicPhysObject::~DynamicPhysObject() {
}

DynamicPhysObject::DynamicPhysObject() : IPhysicalObject() {
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
		DynamicPhysObject* dynPhObj = nullptr;
		Vector2f resolPnt;
		//bool isSlide;
		for (auto coll : colls) {
			if (coll == this ||
				!coll->IsSolidCollision())
				continue;

			//dynPhObj = dynamic_cast<DynamicPhysObject*>(coll);
			//isSlide = (dynPhObj == nullptr) || (!dynPhObj->HasMoved);
			resolPnt = GetResolvingPnt(coll->GetCollider(),GetPrevMovStep(), true);
			SetGlobalPosition(resolPnt);
			++resolCount;
			if (resolCount >= max)
				break;
		}
		HasMoved = false;
	}
}