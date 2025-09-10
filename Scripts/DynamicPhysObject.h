#pragma once

#include <vector>
#include <IPhysicalObject.h>
#include <ICallbackRec_LUpd.h>
#include <IStepTracingObj.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Physics {
	class DynamicPhysObject :public IPhysicalObject, public virtual ICallbackRec_LUpd, public virtual IStepTracingObj{
	public:
		virtual ~DynamicPhysObject();

		void Update(CallbackRecArgs_LUpd args) override;

		bool GetHasMovedState() const {
			return HasMoved;
		}

	protected:
		DynamicPhysObject();

		virtual Vector2f GetResolvingPnt(const ColliderShape& objShape,Vector2f movDir,bool isSlideColl=true) const = 0;

		bool HasMoved = false;
	};
}