#pragma once

#include <SFML/Graphics.hpp>
#include <EngineCallbacks.h>
#include <ICallbackRec_Upd.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;


namespace KrostganEngine {
	namespace Core {
		class EngineMode {
		public:
			virtual void ExecuteCycle() = 0;
		protected:
			EngineMode() {}
		};

		class GameMode:public EngineMode {
			class GameModeInputHandler :public ICallbackRec_Upd {
			public:
				GameModeInputHandler();
				void Update(CallbackRecArgs_Upd args) override;
			};

			void ExecuteCycle() override;
		public:
			GameMode();
			~GameMode();
		private:
			RenderWindow* Window;
			ICallbackRec_Upd* InputHandler;
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
