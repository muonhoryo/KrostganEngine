#pragma once

#include <vector>
#include <EngineCallbacks.h>
#include <LevelLoading.h>

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
			EngineUpdateModule(RenderWindow& Window);

			void Execute() override;

			void Initialize(forward_list<ICallbackRec_Upd*> graphs);
			void Unload();
			void Remove( ICallbackRec_Upd * const& scrToDel);
			void Add(ICallbackRec_Upd*& scrToDel);
		private:
			RenderWindow& Window;
			Event& UpdateEvent;
			forward_list<ICallbackRec_Upd*>& UpdateScripts;
		};

		class EngineRenderModule :EngineWorkCycleModule {
		public:
			EngineRenderModule(RenderWindow& Window);

			void Execute() override;

			void Initialize(forward_list<ICallbackRec_GraphRen*> graphs);
			void Unload();
			void Remove(ICallbackRec_GraphRen * const& graphToDel);
			void Add(ICallbackRec_GraphRen*& graphToAdd);
		private:
			forward_list<ICallbackRec_GraphRen*>& Graphics;
			RenderWindow& Window;
		};

		class EngineLateUpdateModule :EngineWorkCycleModule {
			void Execute() override;
		};
	}
}