#pragma once

#include <WorldTransfObj.h>
#include <AutoAttackInfo.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class AutoAttackAnimation {

	public:
		virtual ~AutoAttackAnimation(){}

		virtual void OnDealDmg(AutoAttackInfo attInfo) = 0;

	protected:
		AutoAttackAnimation(WorldTransfObj& Owner)
			:Owner(Owner)
		{}

		WorldTransfObj& Owner;
	};
}