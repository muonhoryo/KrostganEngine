#pragma once

#include <forward_list>

using namespace std;

namespace KrostganEngine {

	class NoArgsEventHandler;

	class INoArgsEventSubscriber {
	public:
		virtual void Execute() = 0;

	protected:
		INoArgsEventSubscriber() {};
	};


	class NoArgsExecutedEvent final {
	public:
		NoArgsExecutedEvent():
			Subscribers(forward_list<INoArgsEventSubscriber*>()){

		}
		void Add(INoArgsEventSubscriber& subscriber) {
			Subscribers.push_front(&subscriber);
		}
		void Remove(INoArgsEventSubscriber& subscriber) {
			Subscribers.remove(&subscriber);
		}

		friend class NoArgsEventHandler;

	private:
		forward_list<INoArgsEventSubscriber*> Subscribers;
	};

	class NoArgsEventHandler final {
	private:
		NoArgsExecutedEvent& Owner;
	public:
		NoArgsEventHandler(NoArgsExecutedEvent& Owner) :Owner(Owner) {
		}
		void Execute()  {

			typename forward_list< INoArgsEventSubscriber*>::iterator it = Owner.Subscribers.begin();
			typename forward_list< INoArgsEventSubscriber*>::iterator end = Owner.Subscribers.end();
			int size = distance(it, end);
			vector<INoArgsEventSubscriber*> subscrs = vector<INoArgsEventSubscriber*>(size);

			for (int i = 0;it != end;) {

				subscrs[i] = *it;
				++i;
				++it;
			}

			for (INoArgsEventSubscriber* sub : subscrs)
			{
				sub->Execute();
			}
		}
	};
}