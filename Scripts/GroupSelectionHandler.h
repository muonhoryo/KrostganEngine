#pragma once
#include <EngineCore.h>
#include <SFML/System.hpp>
#include <CoreUIUX.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::PlayerControl {
	class GroupSelectionHandler:public ICallbackRec_Upd
	{
	public:
		GroupSelectionHandler();
		~GroupSelectionHandler();

		void Update(CallbackRecArgs_Upd args) override;

	private:
		bool IsInSelProcess;
		Vector2f SelectionStart;
		Vector2f SelectionEnd;
		GroupSelectionQuad* SelectionUIQuad;

		void SelectionStartCheck(const Event& ev);
		void SelectionEndCheck(const Event& ev);
		Vector2f GetCursorGlobalPos();

		static const PhysicsLayer SELECTION_LAYER;
	};
}


