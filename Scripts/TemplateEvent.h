#pragma once

#include <forward_list>

using namespace std;

namespace KrostganEngine {
	
	template <typename TArguments> class EventHandler;

	template <typename TArguments>
	class IEventSubscriber {
	public:
		virtual void Execute(const TArguments& args)=0;

	protected:
		IEventSubscriber() {};
	};

	template <typename TArguments>
	class ExecutedEvent final {
	public:
		ExecutedEvent() {
			Subscribers = forward_list<IEventSubscriber<TArguments>*>();
		}
		void Add(IEventSubscriber<TArguments>* subscriber) {
			Subscribers.push_front(subscriber);
		}
		void Remove(IEventSubscriber<TArguments>* subscriber) {
			Subscribers.remove(subscriber);
		}

		template <typename TArgs>
		friend void EventHandler<TArgs>::Execute(const TArgs& args);

	private:
		forward_list<IEventSubscriber<TArguments>*> Subscribers;
	};

	template <typename TArguments=void>
	class EventHandler final {
	private:
		ExecutedEvent<TArguments>& Owner;
	public:
		EventHandler(ExecutedEvent<TArguments>& Owner):Owner(Owner) {
		}
		void Execute(const TArguments& args) {
			for (IEventSubscriber<TArguments>* sub : Owner.Subscribers)
			{
				sub->Execute(args);
			}
		}
	};
}