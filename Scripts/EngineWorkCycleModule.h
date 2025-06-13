#pragma once

#include <forward_list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ICallbackRec_GraphRen.h>
#include <ICallbackRec_Upd.h>
#include <ICallbackRec_LUpd.h>
#include <ICallbackRec_GraphPostRen.h>

using namespace sf;
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
		void Remove( TCallback& callbckToDel) {
			TCallback* elRef = Callbacks.front();
			if (elRef == &callbckToDel)
			{
				Callbacks.pop_front();
				return;
			}
			bool isFound = false;
			auto itToD = Callbacks.begin();
			auto it = Callbacks.begin();
			++it;
			for (; it != Callbacks.end(); ++it) {
				elRef = *it;
				if (elRef== &callbckToDel) {
					isFound = true;
					break;
				}
				++itToD;
			}
			if(isFound)
				Callbacks.erase_after(itToD);
		};
		void Add(TCallback& callbck) {
			Callbacks.push_front(&callbck);
		};

	protected:
		EngineCallbackHandler() : Callbacks(*new forward_list<TCallback*>) {};

		forward_list<TCallback*>& Callbacks;

		friend class EngineWorkCycleModule;
		friend class EngineRenderModule;
	};

	class EngineUpdateModule : public EngineWorkCycleModule, public EngineCallbackHandler<ICallbackRec_Upd> {
	public:
		EngineUpdateModule(RenderWindow& Window);

		void Execute() override;

	private:
		RenderWindow& Window;
		Event& UpdateEvent;
		vector<Event> PlayerInput;
		Clock FrameDeltaTimer;

	public:
		void SetFrameDeltaTime(float time);
	};

	class EngineRenderModule :public EngineCallbackHandler<ICallbackRec_GraphRen>, public EngineCallbackHandler<ICallbackRec_GraphPostRen>,
		public EngineWorkCycleModule {
	public:
		EngineRenderModule(RenderWindow& Window);

		void Execute() override;

	private:
		RenderWindow& Window;
		Clock FrameRenderTime;

		//EngineCallbackHandler<ICallbackRec_GraphRen> ObjectsRender;
		//EngineCallbackHandler<ICallbackRec_GraphPostRen> UIRender;
	
	public:
		/*EngineCallbackHandler<ICallbackRec_GraphRen> const& GetObjectsRender() const {
			return ObjectsRender;
		}
		EngineCallbackHandler<ICallbackRec_GraphPostRen> const& GetUIRender() const {
			return UIRender;
		}*/

		void SetFrameRenderTime(float time);
	};

	class EngineLateUpdateModule :public EngineCallbackHandler<ICallbackRec_LUpd>,
		public EngineWorkCycleModule {

	public:
		EngineLateUpdateModule();

		void Execute() override;
	};
}