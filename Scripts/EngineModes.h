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

	/*class StartMessageMode :public EngineMode {

	private:
		class StartMsgInputHandler :public ICallbackRec_Upd {

		public:
			StartMsgInputHandler() {

			}
			~StartMsgInputHandler() {
				delete LoadMessage;
			}

			void Update(CallbackRecArgs_Upd args) override;

			bool		HasPressed = false;
			UIText*		LoadMessage = nullptr;
		};

	private:
		UIText					Message;
		StartMsgInputHandler	InputHandler;

		static inline const string MessageText = "Welcome to sector 17 of the Krostgan's Valley, commander.\n"
			"Your current objective is eleminating the enemy's hero.\n"
			"The enemy is superior to you, but their fighters are same like your mercenaries,\n"
			"and the forces are unevenly distributed throughout the location.\n"
			"Press Enter to proceed to combat.\n"
			"Good luck!";
		static inline const Vector2f MESSAGE_ANCHOR = Vector2f(0.25, 0.25);
		static inline const Vector2f LOAD_MESSAGE_ANCHOR = Vector2f(0.9, 0.9);

	public:
		StartMessageMode();

		void ExecuteCycle() override;

	};*/
}
