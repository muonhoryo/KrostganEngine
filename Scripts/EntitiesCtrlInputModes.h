#pragma once

#include <EntitiesCtrlInputHandler.h>
#include <Physics.h>
#include <CoreVisual_UI.h>

using namespace KrostganEngine::UI;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;

namespace KrostganEngine::PlayerControl {
	class EntCtrlMode_Base :public EntitiesCtrlInputMode {
	public:
		EntCtrlMode_Base(EntitiesCtrlInputHandler& Owner);

		void HandleInput(CallbackRecArgs_Upd& args) override;

	private:
		static bool AbleToGiveOrders();
	};

	class EntCtrlMode_AttackOrder :public EntitiesCtrlInputMode {
	public:
		EntCtrlMode_AttackOrder(EntitiesCtrlInputHandler& Owner);
		~EntCtrlMode_AttackOrder() override;

		void HandleInput(CallbackRecArgs_Upd& args) override;
	};

	class EntCtrlMode_GroupSelect :public EntitiesCtrlInputMode {
	public:
		EntCtrlMode_GroupSelect(EntitiesCtrlInputHandler& Owner, Vector2f startMousePos);
		~EntCtrlMode_GroupSelect() override;

		void HandleInput(CallbackRecArgs_Upd& args) override;

	private:
		Vector2f SelectionStart;
		Vector2f SelectionEnd;
		GroupSelectionQuad* SelectionUIQuad;

		Vector2f GetCursorGlobalPos();

		static const PhysicsLayer SELECTION_LAYER;
	};
}