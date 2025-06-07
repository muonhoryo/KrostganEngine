#pragma once

#include <vector>
#include <IPhysicalObject.h>
#include <ICallbackRec_LUpd.h>

using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Physics {
	class DynamicPhysObject :public IPhysicalObject, public virtual ICallbackRec_LUpd{
	public:
		virtual ~DynamicPhysObject();

		void SetPosition(Vector2f position) override;

		void Update(CallbackRecArgs_LUpd args) override;

		Vector2f GetLastMoveDirection() const {
			return MoveDirection;
		}
		bool GetHasMovedState() const {
			return HasMoved;
		}

	protected:
		DynamicPhysObject();

		virtual Vector2f GetResolvingPnt(const ColliderShape& objShape,Vector2f movDir ) const = 0;

	private:
		bool HasMoved = false;
		Vector2f MoveDirection;
	};
}