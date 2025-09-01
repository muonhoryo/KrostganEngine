#pragma once

#include <forward_list>
#include <list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ICallbackRec_GraphRen.h>
#include <ICallbackRec_Upd.h>
#include <ICallbackRec_LUpd.h>
#include <ICallbackRec_GraphPostRen.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Core {

	static bool PostRenCallbks_SortPred(ICallbackRec_GraphPostRen*const& first, ICallbackRec_GraphPostRen*const& second) {
		return first->GetRendLayer() < second->GetRendLayer();
	}

	class EngineWorkCycleModule {
	public:
		virtual void Execute() = 0;

	protected:
		EngineWorkCycleModule() {};
	};

	template<typename TCallback>
	class EngineCallbackHandler {
	public:
		virtual void Unload() {
			
			IsIteratingCallbacks = true;

			if (DelayedDelCallbksCount > 0)
				DeleteDelayedCallbacks();

			if (Callbacks.size() > 0) {
				auto it = Callbacks.end();
				auto end = Callbacks.begin();
				--it;
				for (;it != end;--it) {
					if (*it != nullptr) {

						*it = nullptr;
					}
				}
				*it = nullptr;
				Callbacks.clear();

				DelayedDelCallbksCount = 0;
				DelayedDelCallbks.clear();
			}

			IsIteratingCallbacks = false;
		}
		virtual void Remove(TCallback& callbckToDel) {

			TCallback* elRef = Callbacks.front();
			bool isFound = false;
			auto itToD = Callbacks.begin();
			size_t offset = 0;
			if (elRef==&callbckToDel) {

				isFound = true;
			}
			if (!isFound) {
				++offset;
				++itToD;
				for (; itToD != Callbacks.end(); ++itToD) {
					elRef = *itToD;
					if (elRef==&callbckToDel) {
						isFound = true;
						break;
					}
					++offset;
				}
			}
			if (isFound)
			{
				if (IsIteratingCallbacks) {

					*itToD = nullptr;
					DelayedDelCallbks.push_front(offset);
					++DelayedDelCallbksCount;
				}
				else {
					
					if (DelayedDelCallbksCount > 0)
						DeleteDelayedCallbacks();

					Callbacks.erase(itToD);
				}
			}
		};
		/// <summary>
		/// Return reference to watch_ptr_wr with added pointer of callbck
		/// </summary>
		/// <param name="callbck"></param>
		/// <returns></returns>
		virtual void Add(TCallback& callbck) {

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
				typename list<TCallback*>::iterator it;
				while (DelayedDelCallbksCount > 0) {
					it = Callbacks.begin();
					for (size_t i = 0;i < DelayedDelCallbks.front();i++) {
						++it;
					}
					Callbacks.erase(it);
					DelayedDelCallbks.pop_front();
					--DelayedDelCallbksCount;
				}
			}
		}

	protected:
		EngineCallbackHandler() {};

		//void Sort(int (*PR)(TCallback*,TCallback*)) {
		//	Callbacks.sort(PR);
		//}

		list<TCallback*> Callbacks = list<TCallback*>();

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

		void Add(ICallbackRec_GraphPostRen& callbck) override;

	private:

		RenderWindow& Window;
		Clock FrameRenderTime;
		bool NeedToSort = true;

	public:

		void SetFrameRenderTime(float time);
		void SetNeedToSort();
	};

	class EngineLateUpdateModule :public EngineCallbackHandler<ICallbackRec_LUpd>,
		public EngineWorkCycleModule {

	public:
		EngineLateUpdateModule();

		void Execute() override;
	};
}