#pragma once

#include <forward_list>
#include <vector>

using namespace std;

namespace KrostganEngine {
	
	template <typename TArguments> class EventHandler;

	template <typename TArguments>
	class IEventSubscriber {
	public:
		virtual void Execute(TArguments& args)=0;

	protected:
		IEventSubscriber() {};
	};

	template <typename TArguments>
	class ExecutedEvent final {
	public:
		ExecutedEvent():
			Subscribers(forward_list<IEventSubscriber<TArguments>*>()){

		}
		void Add(IEventSubscriber<TArguments>& subscriber) {
			Subscribers.push_front(&subscriber);
		}
		void Remove(IEventSubscriber<TArguments>& subscriber) {
			Subscribers.remove(&subscriber);
		}

		template <typename TArgs>
		friend void EventHandler<TArgs>::Execute(TArgs& args);

	private:
		forward_list<IEventSubscriber<TArguments>*> Subscribers;
	};

	template <typename TArguments=void>
	class EventHandler final {
	//private:
	public:
		ExecutedEvent<TArguments>& Owner;
	public:
		EventHandler(ExecutedEvent<TArguments>& Owner):Owner(Owner) {
		}
		void Execute(TArguments& args) {

			auto it = Owner.Subscribers.cbegin();
			auto end = Owner.Subscribers.cend();
			size_t size = distance(it,end);
			vector<IEventSubscriber<TArguments>*> subscrs = vector<IEventSubscriber<TArguments>*>(size);

			for (int i = 0;it != end;) {

				subscrs[i] = *it;
				++i;
				++it;
			}

			for (IEventSubscriber<TArguments>* sub : subscrs)
			{
				sub->Execute(args);
			}
		}
	};
}