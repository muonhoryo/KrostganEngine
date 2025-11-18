#pragma once

#include <AutoAttackModule.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {

	struct AAProjectileCtorParams_NoTar : public AAProjectileCtorParams {

		AAProjectileCtorParams_NoTar(AutoAttackModule& Owner, Vector2f TarPos)
			:AAProjectileCtorParams(Owner),
			TarPos(TarPos)
		{}

		Vector2f TarPos;
	};

	class AAProj_NoTar : public AutoAttackProjectile {

	public:
		AAProj_NoTar(const AAProjectileCtorParams_NoTar& params)
			:AutoAttackProjectile(params),
			TarPos(params.TarPos)
		{}
		virtual ~AAProj_NoTar(){}

	protected:
		bool CheckTargetReachability() const override {
			return true;
		}
		Vector2f GetTargetPosition() const override {
			return TarPos;
		}
		void CollideWithTarget() override {
			DealDmgByAOE(TarPos);
			delete this;
		}

		Vector2f TarPos;
	};
}