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
		/*void Initialize(forward_list < TCallback*> callbacks) {
			Unload();
			for (TCallback* cb : callbacks) {

				Add(*cb);
			}
		};
		void Unload() {
			Callbacks.clear();
		};*/
		void Remove(TCallback& callbckToDel) {

			TCallback* elRef = Callbacks.front();
			bool isFound = false;
			auto itToD = Callbacks.before_begin();
			size_t offset = 0;
			if (elRef == &callbckToDel) {

				isFound = true;
			}
			auto it = Callbacks.begin();
			if (!isFound) {
				++offset;
				++itToD;
				++it;
				for (; it != Callbacks.end(); ++it) {
					elRef = *it;
					if (elRef == &callbckToDel) {
						isFound = true;
						break;
					}
					++itToD;
					++offset;
				}
			}
			if (isFound)
			{
				if (IsIteratingCallbacks) {

					*(++itToD) = nullptr;
					DelayedDelCallbks.push_front(offset);
					++DelayedDelCallbksCount;
				}
				else {
					
					if (DelayedDelCallbksCount > 0)
						DeleteDelayedCallbacks();

					Callbacks.erase_after(itToD);
				}
			}
		};
		void Add(TCallback& callbck) {

			Callbacks.push_front(&callbck);
			if (DelayedDelCallbksCount > 0) {

				for (auto& it : DelayedDelCallbks)
				{
					++it;
				}
			}
		};

		void DeleteDelayedCallbacks() {

			if (DelayedDelCallbksCount != 0) {

				DelayedDelCallbks.sort(greater<>());
				typename forward_list<TCallback*>::iterator it;
				while (DelayedDelCallbksCount > 0) {
					it = Callbacks.before_begin();
					for (size_t i = 0;i < DelayedDelCallbks.front();i++) {
						++it;
					}
					Callbacks.erase_after(it);
					DelayedDelCallbks.pop_front();
					--DelayedDelCallbksCount;
				}
			}
		}

	protected:
		EngineCallbackHandler() {};

		forward_list<TCallback*> Callbacks = forward_list<TCallback*>();

		bool IsIteratingCallbacks = false;

	private:
		/// <summary>
		/// Offset for iterators to element before target to delete
		/// </summary>
		forward_list<size_t> DelayedDelCallbks = forward_list<size_t>();
		size_t DelayedDelCallbksCount = 0;

		friend class EngineRenderModule;
		friend class EngineWorkCycleModule;
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

	
	public:

		void SetFrameRenderTime(float time);
	};

	class EngineLateUpdateModule :public EngineCallbackHandler<ICallbackRec_LUpd>,
		public EngineWorkCycleModule {

	public:
		EngineLateUpdateModule();

		void Execute() override;
	};
}