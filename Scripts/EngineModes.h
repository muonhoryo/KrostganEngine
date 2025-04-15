#pragma once

#include <EngineCore.h>

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
			GameMode():EngineMode(){}
		};

		class MainMenuMode :public EngineMode {
			void ExecuteCycle() override;

		public:
			MainMenuMode():EngineMode(){}
		};
	}
}
