
#include <watch_ptr.h>

using namespace KrostganEngine;

watch_ptr_handler::watch_ptr_handler(watch_ptr& Owner) 
	:Owner(Owner){

	++Owner.handlerCount;
}

watch_ptr_handler::watch_ptr_handler(const watch_ptr_handler& Copy) : watch_ptr_handler(Copy.Owner){

}

watch_ptr_handler::~watch_ptr_handler() {

	--Owner.handlerCount;
	if (Owner.handlerCount == 0 && Owner.GetPtr()==nullptr)
		delete &Owner;
}