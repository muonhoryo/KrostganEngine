#pragma once

#include <watch_ptr.h>

using namespace KrostganEngine;

namespace KrostganEngine::EntitiesControl {
	class ISelectableEntity : public virtual w_ptr_observable{
	public:
		virtual ~ISelectableEntity(){}

		virtual void SelectionOn()=0;
		virtual void SelectionOff()=0;
		virtual bool IsSelected() = 0;

	protected:
		ISelectableEntity(){}
	};
}