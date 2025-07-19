
#include <watch_ptr.h>

using namespace KrostganEngine;

watch_ptr_handler_c::watch_ptr_handler_c(watch_ptr& Owner)	: watch_ptr_handler(Owner) {

}
watch_ptr_handler_c::watch_ptr_handler_c(const watch_ptr_handler& Copy) : watch_ptr_handler(Copy) {

}
watch_ptr_handler_c::watch_ptr_handler_c(const watch_ptr_handler_c& Copy) : watch_ptr_handler(Copy) {

}
