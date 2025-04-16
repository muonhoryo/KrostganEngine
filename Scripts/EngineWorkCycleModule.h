#pragma once

#include <vector>
#include <EngineCallbacks.h>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine {
	namespace Core {
		class EngineWorkCycleModule {
		public:
			virtual void Execute()=0;

		protected:
			EngineWorkCycleModule() {};
		};

		class EngineUpdateModule:EngineWorkCycleModule {
		public:
			void Execute() override;
		};

		class EngineRenderModule :EngineWorkCycleModule {
		public:
			EngineRenderModule();

			void Execute() override;
			void Initialize(vector<ICallbackRec_GraphRen*> graphs);
			void Remove(const ICallbackRec_GraphRen*& graphToDel);
			void Add(ICallbackRec_GraphRen*& graphToAdd);
		private:
			vector<ICallbackRec_GraphRen*> Graphics;
		};

		class EngineLateUpdateModule :EngineWorkCycleModule {
			void Execute() override;
		};
	}
}