#pragma once

namespace KrostganEngine::EntitiesControl {
	class IEntityAction {
	public:
		virtual bool CheckExecCondition() = 0;
		virtual void Execute() = 0;

	protected:
		IEntityAction(){}
	};
}