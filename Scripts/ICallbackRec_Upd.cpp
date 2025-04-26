
#include <EngineCore.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_Upd::ICallbackRec_Upd() {
	ICallbackRec_Upd* cb = this;
	Engine::GetUpdateModule().Add(cb);
}
ICallbackRec_Upd::~ICallbackRec_Upd() {
	ICallbackRec_Upd* cb = this;
	Engine::GetUpdateModule().Remove(cb);
}
