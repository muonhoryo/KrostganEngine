#pragma once

#include <TransformableObj.h>
#include <AutoAttackInfo.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class AutoAttackAnimation {

	public:
		virtual ~AutoAttackAnimation(){}

		virtual void OnDealDmg(AutoAttackInfo attInfo) = 0;

	protected:
		AutoAttackAnimation(TransformableObj& Owner)
			:Owner(Owner)
		{}

		TransformableObj& Owner;
	};
}