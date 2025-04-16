#pragma once

#include <SFML/Graphics.hpp>
#include <EngineCore.h>

using namespace sf;

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
		private:
			RenderWindow* Window;
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
