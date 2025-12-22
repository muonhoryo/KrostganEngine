#pragma once

#include <SFML/Graphics.hpp>
#include <ICallbackRec_Upd.h>
#include <CoreEntitiesControl.h>
#include <CorePlayerControl.h>
#include <CoreVisual_UI.h>
#include <ExtVisual.h>

using namespace sf;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Core {
	class EngineMode {
	public:
		virtual ~EngineMode(){}

		virtual void ExecuteCycle() = 0;
	protected:
		EngineMode() {}
	};

	class GameMode :public EngineMode {

	public:
		GameMode();
		virtual ~GameMode();

		void ExecuteCycle() override;

	private:
		ExtVisualManager*			GameInterface;
	};

	class MainMenuMode :public EngineMode {

	public:
		MainMenuMode();
		virtual ~MainMenuMode();

		void ExecuteCycle() override;
	};

	class LevelDeserializationMode :public EngineMode {
		void ExecuteCycle() override;

	public:
		LevelDeserializationMode() : EngineMode() {};
		virtual ~LevelDeserializationMode(){}
	};
}
