
#include <watch_ptr.h>

using namespace KrostganEngine;

watch_ptr_handler& watch_ptr::GetPtrHandler() {

	watch_ptr& ref = *this;
	return *new watch_ptr_handler(ref);
}

void watch_ptr::Reset() {
	target = nullptr;
	if (handlerCount == 0)
		delete this;
}