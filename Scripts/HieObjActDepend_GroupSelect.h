#pragma once

#include <HieObjActDependency.h>
#include <UIElement.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class HieObjActDepend_GroupSelect final : public HieObjActDependency{

	public:
		HieObjActDepend_GroupSelect(UIElement& TargetEl,
			int SelectionThreshold = 1, bool GreaterToActivate = true, bool EqualToActivate = true)
			:HieObjActDependency(), 
				TargetEl(TargetEl),
				SelectionThreshold(SelectionThreshold),
				GreaterToActivate(GreaterToActivate),
				EqualToActivate(EqualToActivate)
				
		{
			Update();
		}
		virtual ~HieObjActDepend_GroupSelect() {}

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
	};
}