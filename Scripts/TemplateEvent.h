#pragma once

#include <forward_list>
#include <vector>

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
		ExecutedEvent():
			Subscribers(forward_list<IEventSubscriber<TArguments>*>()){

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

			typename forward_list< IEventSubscriber<TArguments>*>::iterator it = Owner.Subscribers.begin();
			typename forward_list< IEventSubscriber<TArguments>*>::iterator end = Owner.Subscribers.end();
			int size = distance(it,end);
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