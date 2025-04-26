#pragma once

namespace KrostganEngine::EntitiesControl {
	class ISelectableEntity {
	public:
		virtual void SelectionOn()=0;
		virtual void SelectionOff()=0;
		virtual bool IsSelected() = 0;

	protected:
		ISelectableEntity(){}
	};
}