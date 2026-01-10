#pragma once

#include <IEntityUIDependency.h>
#include <GetEntStatsWrapperFunc.h>
#include <HieObjActDependency.h>
#include <UIElement.h>

namespace KrostganEngine::UI {

	class HieObjActDepend_AutoAtkActivity :public HieObjActDependency, public IEntityUIDependency {

	public:
		HieObjActDepend_AutoAtkActivity
		(UIElement& TargetEl,
			const GetEntStatsWrapperFunc& GetStatsFunc,
			bool IsActiveOnAA)
				:HieObjActDependency(),
					TargetEl(TargetEl),
					GetStatsFunc(GetStatsFunc),
					IsActiveOnAA(IsActiveOnAA){

			Update();
		}
		virtual ~HieObjActDepend_AutoAtkActivity() {}

		void ChangeDepTarget(Entity* target) override {

			if (target != nullptr) {

				bool isAbleToAA = target->GetBattleStats().GetCurrAAStatsIndex() != -1;
				TargetEl.SetActivity(isAbleToAA == IsActiveOnAA);
			}
		}

		void Set_IsActiveOnAA(bool IsActiveOnAA) {
			this->IsActiveOnAA = IsActiveOnAA;
			Update();
		}

	protected:
		void Update() override {

			auto target = GroupSelectionSystem::GetFirstChoosen();
			auto parTar = dynamic_cast<Entity*>(target);
			ChangeDepTarget(parTar);
		}

	private:
		const GetEntStatsWrapperFunc& GetStatsFunc;
		UIElement& TargetEl;
		bool IsActiveOnAA;
	};
}