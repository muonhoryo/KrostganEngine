

#include <Event.h>
#include <forward_list>

using namespace KrostganEngine;


template<typename TArguments>
void EventHandler<TArguments>::Execute(TArguments& args) {
	for (IEventSubscriber<TArguments>* sub : Owner.Subscribers)
	{
		sub.Execute(args);
	}
}