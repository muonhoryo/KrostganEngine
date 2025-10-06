#pragma once

#include <GroupSelectionSystem.h>
#include <UIElement.h>
#include <ValueDependency.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class HieObjActDepend_GroupSelect final : public IUIDependency{

	private:
		class ChangeFirstSelSubsc final : public INoArgsEventSubscriber{

		public:
			ChangeFirstSelSubsc(HieObjActDepend_GroupSelect& Owner)
				:Owner(Owner)
			{}

			void Execute() override {
				Owner.Update();
			}

		private:
			HieObjActDepend_GroupSelect& Owner;
		};

	public:
		HieObjActDepend_GroupSelect(UIElement& TargetEl,
			int SelectionThreshold = 1, bool GreaterToActivate = true, bool EqualToActivate = true)
			:TargetEl(TargetEl),
			SelectionThreshold(SelectionThreshold),
			GreaterToActivate(GreaterToActivate),
			EqualToActivate(EqualToActivate)
		{
			Subsc = new ChangeFirstSelSubsc(*this);
			GroupSelectionSystem::ChangeSelectablesEvent.Add(*Subsc);
			Update();
		}
		virtual ~HieObjActDepend_GroupSelect() {
			GroupSelectionSystem::ChangeSelectablesEvent.Remove(*Subsc);
			delete Subsc;
		}

		int GetSelectionThreshold() const { return SelectionThreshold; }
		bool GetGreaterToActivateCond() const { return GreaterToActivate; }
		bool GetEqualToActivateCond() const { return EqualToActivate; }
		void SetSelectionThreshold(int threshold) {
			SelectionThreshold = threshold;
			Update();
		}
		void SetGreaterCondition(bool greaterToActive) {
			GreaterToActivate = greaterToActive;
			Update();
		}
		void SetEqualCondition(bool equalToActivate) {
			EqualToActivate = equalToActivate;
			Update();
		}

	protected:
		void Update() override {
			size_t count = GroupSelectionSystem::GetSelectionCount();
			if (count > SelectionThreshold == GreaterToActivate ||
				(count == SelectionThreshold) == EqualToActivate)
				TargetEl.SetActivity(true);
			else
				TargetEl.SetActivity(false);
		}

	private:
		UIElement&	TargetEl;
		int			SelectionThreshold;
		bool		GreaterToActivate;
		bool		EqualToActivate;
		ChangeFirstSelSubsc* Subsc;

		friend class ChangeFirstSelSubsc;
	};
}