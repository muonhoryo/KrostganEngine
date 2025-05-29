#pragma once

namespace KrostganEngine::EntitiesControl {
	class IEntityAction {
	public:
		virtual ~IEntityAction(){}

		virtual bool CheckExecCondition() = 0;
		virtual void Execute() = 0;

	protected:
		IEntityAction():IsDataInv(false) { }

		bool IsDataInv;
	};
}