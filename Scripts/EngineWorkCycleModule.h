#pragma once

#include <forward_list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ICallbackRec_GraphRen.h>
#include <ICallbackRec_Upd.h>
#include <ICallbackRec_LUpd.h>

using namespace std;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Core {
	class EngineWorkCycleModule {
	public:
		virtual void Execute() = 0;

	protected:
		EngineWorkCycleModule() {};
	};

	template<typename TCallback>
	class EngineCallbackHandler {
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
			if (Callbacks.front() == callbckToDel)
			{
				Callbacks.pop_front();
				return;
			}
			auto itToD = Callbacks.begin();
			auto it = Callbacks.begin();
			++it;
			for (; it != Callbacks.end(); ++it) {
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
		EngineCallbackHandler() : Callbacks(*new forward_list<TCallback*>) {};

		forward_list<TCallback*>& Callbacks;
	};

	class EngineUpdateModule :public EngineCallbackHandler<ICallbackRec_Upd>,
		public EngineWorkCycleModule {
	public:
		EngineUpdateModule(RenderWindow& Window);

		void Execute() override;
	private:
		RenderWindow& Window;
		Event& UpdateEvent;
		vector<Event> PlayerInput;
	};

	class EngineRenderModule :public EngineCallbackHandler<ICallbackRec_GraphRen>,
		public EngineWorkCycleModule {
	public:
		EngineRenderModule(RenderWindow& Window);

		void Execute() override;
	private:
		RenderWindow& Window;
	};

	class EngineLateUpdateModule :public EngineCallbackHandler<ICallbackRec_LUpd>,
		public EngineWorkCycleModule {
		void Execute() override;
	};
}