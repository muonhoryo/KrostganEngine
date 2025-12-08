#pragma once

#include <forward_list>
#include <list>

using namespace std;

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
		void Unload() {
			
			IsIteratingCallbacks = true;

			if (DelayedDelCallbksCount > 0)
				DeleteDelayedCallbacks();

			if (Callbacks.size() > 0) {

				list<TCallback*> savedRecs = list<TCallback*>();

				auto it = Callbacks.rbegin();
				auto end = Callbacks.rend();
				for (;it != end;++it) {
					if (*it != nullptr) {

						if ((*it)->IsDestroyedOnUnload()) {
							delete* it;
							*it = nullptr;
						}
						else {
							savedRecs.push_back(*it);
						}
					}
				}
				Callbacks.clear();

				for (auto rec : savedRecs) {
					Callbacks.push_front(rec);
				}
				savedRecs.clear();

				DelayedDelCallbksCount = 0;
				DelayedDelCallbks.clear();
			}

			IsIteratingCallbacks = false;
			OnUnload();
		}
		void Remove(TCallback& callbckToDel) {

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
					OnRemoveCallback();
				}
			}
			OnTryRemoveCallback();
		};
		/// <summary>
		/// Return reference to watch_ptr_wr with added pointer of callbck
		/// </summary>
		/// <param name="callbck"></param>
		/// <returns></returns>
		void Add(TCallback& callbck) {

			Callbacks.push_front(&callbck);
			if (DelayedDelCallbksCount > 0) {

				for (auto& it : DelayedDelCallbks)
				{
					++it;
				}
			}
			OnAddCallback(callbck);
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
					OnRemoveCallback();
					DelayedDelCallbks.pop_front();
					--DelayedDelCallbksCount;
				}
			}
		}

		bool Get_IsIteratingCallbacks() const {
			return IsIteratingCallbacks;
		}
		size_t GetCallbacksCount() const {
			return Callbacks.size();
		}

	protected:
		EngineCallbackHandler() {};

		list<TCallback*> Callbacks = list<TCallback*>();
		bool IsIteratingCallbacks = false;

		virtual void OnAddCallback(TCallback& callbck) {}

		virtual void OnRemoveCallback(){}
		virtual void OnTryRemoveCallback(){}

		virtual void OnUnload(){}

	private:
		/// <summary>
		/// Offset for iterators to element before target to delete
		/// </summary>
		forward_list<size_t> DelayedDelCallbks = forward_list<size_t>();
		size_t DelayedDelCallbksCount = 0;

		friend class EngineRenderModule;
		friend class EngineWorkCycleModule;
	};
}