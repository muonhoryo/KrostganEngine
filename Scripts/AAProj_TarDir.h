#pragma once

#include <AutoAttackModule.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {

	struct AAProjectileCtorParams_TarDir : public AAProjectileCtorParams{

		AAProjectileCtorParams_TarDir(AutoAttackModule& Owner, watch_ptr_handler_wr<IAttackableObj> Target)
			:AAProjectileCtorParams(Owner),
			Target(Target){

		}

		watch_ptr_handler_wr<IAttackableObj> Target;
	};

	class AAProj_TarDir : public AutoAttackProjectile {

	public:
		AAProj_TarDir(const AAProjectileCtorParams_TarDir& params)
			:AutoAttackProjectile(params),
			Target(params.Target){

		}
		virtual ~AAProj_TarDir(){}

	protected:
		bool CheckTargetReachability() const override {
			auto ptr = Target.GetPtr_t_c();
			if (ptr == nullptr ||
				!ptr->IsTargetableForAA() ||
				ptr->GetHPModule().DeathModule.GetIsDeadState())
					return false;
			else
				return true;
		}
		Vector2f GetTargetPosition() const override {
			return Target.GetPtr_t_c()->GetGlobalPosition();
		}
		void CollideWithTarget() override {
			bool isSiege;
			if (GetState_IsValidOwnerRef())
				isSiege = Owner.GetCurrAAStats()->GetState_IsSiege();
			else {
				size_t index = AutoAttackStats::GetArrayIndexOfField((int)AAStatType::IsSiege);
				isSiege = CachedAAStats.get()->Params_bool[index];
			}

			if (isSiege)
				DealDmgByAOE(Target.GetPtr_t()->GetGlobalPosition());
			else
				DealDmgToSingleTarget(*Target.GetPtr_t());
			delete this;
		}

		watch_ptr_handler_wr<IAttackableObj> Target;
	};
}