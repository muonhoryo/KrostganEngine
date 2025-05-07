#pragma once

#include <SFML/Graphics.hpp>
#include <ICallbackRec_Upd.h>
#include <CoreEntitiesControl.h>
#include <CorePlayerControl.h>
#include <GameUI.h>

using namespace sf;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::PlayerControl;

namespace KrostganEngine::Core {
	class EngineMode {
	public:
		virtual void ExecuteCycle() = 0;
	protected:
		EngineMode() {}
	};

	class GameMode :public EngineMode {

		void ExecuteCycle() override;
	public:
		GameMode();
		~GameMode();
	private:
		RenderWindow* Window;
		ICallbackRec_Upd* BaseInputHandl;
		EntitiesCtrlInputHandler* EntitiesCtrlHandler;
		GameUI* GameInterface;
	};

	class MainMenuMode :public EngineMode {
		void ExecuteCycle() override;
	public:
		MainMenuMode() :EngineMode() {}
	};

	class LevelDeserializationMode :public EngineMode {
		void ExecuteCycle() override;
	public:
		LevelDeserializationMode() : EngineMode() {};
	};
}
