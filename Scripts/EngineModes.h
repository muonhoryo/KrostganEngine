#pragma once

#include <SFML/Graphics.hpp>
#include <ICallbackRec_Upd.h>
#include <EntitiesControl.h>

using namespace sf;
using namespace KrostganEngine::EntitiesControl;


namespace KrostganEngine {
	namespace Core {
		class EngineMode {
		public:
			virtual void ExecuteCycle() = 0;
		protected:
			EngineMode() {}
		};

		class GameMode:public EngineMode {

			void ExecuteCycle() override;
		public:
			GameMode();
			~GameMode();
		private:
			RenderWindow* Window;
			ICallbackRec_Upd* BaseInputHandl;
			ICallbackRec_Upd* GroupSelectionHandl;
			GroupSelectionSystem* GroupSelectSystem;
		};

		class MainMenuMode :public EngineMode {
			void ExecuteCycle() override;
		public:
			MainMenuMode():EngineMode(){}
		};

		class LevelDeserializationMode:public EngineMode {
			void ExecuteCycle() override;
		public:
			LevelDeserializationMode(): EngineMode() {};
		};
	}
}
