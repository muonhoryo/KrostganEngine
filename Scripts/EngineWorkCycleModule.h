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

		template<typename TCallback>
		class EngineCallbackHandler:public EngineWorkCycleModule {
		public:
			void Initialize(forward_list < TCallback*> callbacks) {
				Unload();
				for (auto cb : callbacks) {
					Callbacks.push_front(cb);
				}
			};
			void Unload() {
				Callbacks.clear();
			};
			void Remove(TCallback* const& callbckToDel) {
				auto itToD = Callbacks.cbegin();
				auto it = Callbacks.begin();
				for (;it != Callbacks.cend();++it) {
					if (*it == callbckToDel) {
						break;
					}
					++itToD;
				}
				Callbacks.erase_after(itToD);
			};
			void Add(TCallback*& callbck) {
				Callbacks.push_front(callbck);
			};

		protected:
			EngineCallbackHandler() :EngineWorkCycleModule(), Callbacks(*new forward_list<TCallback*>) {};

			forward_list<TCallback*>& Callbacks;
		};

		class EngineUpdateModule:public EngineCallbackHandler<ICallbackRec_Upd> {
		public:
			EngineUpdateModule(RenderWindow& Window);

			void Execute() override;
		private:
			RenderWindow& Window;
			Event& UpdateEvent;
			vector<Event> PlayerInput;
		};

		class EngineRenderModule :public EngineCallbackHandler<ICallbackRec_GraphRen> {
		public:
			EngineRenderModule(RenderWindow& Window);

			void Execute() override;
		private:
			RenderWindow& Window;
		};

		class EngineLateUpdateModule :public EngineCallbackHandler<ICallbackRec_LUpd> {
			void Execute() override;
		};
	}
}