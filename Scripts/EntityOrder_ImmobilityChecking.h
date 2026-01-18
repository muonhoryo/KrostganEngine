#pragma once

#include <OrdersExecutor.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_ImmobilityChecking {
	
	public:
		virtual ~EntityOrder_ImmobilityChecking(){}

		OrdersExecutor& Owner;

	protected:
		EntityOrder_ImmobilityChecking(OrdersExecutor& Owner)
			:Owner(Owner){}

		/// <summary>
		/// Return true if owner is staying in a single point
		/// </summary>
		/// <param name="toTargetDist_sqr"></param>
		/// <returns></returns>
		bool CheckImmobility(Vector2f target) const;
		/// <summary>
		/// Return true if owner is staying in a single point
		/// </summary>
		/// <param name="toTargetDist_sqr"></param>
		/// <returns></returns>
		bool CheckImmobility(float toTargetDist_sqr) const;

	private:
		mutable float PrevToTargetDist_Sqr = FLT_MAX;
	};
}