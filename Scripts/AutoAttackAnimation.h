#pragma once

#include <WorldTransfObj.h>
#include <AutoAttackHitInfo.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class AutoAttackAnimation {

	public:
		virtual ~AutoAttackAnimation(){}

		virtual void OnTakeDmg(const AutoAttackHitInfo& attInfo) = 0;

	protected:
		AutoAttackAnimation(WorldTransfObj& Owner)
			:Owner(Owner)
		{}

		WorldTransfObj& Owner;
	};
}