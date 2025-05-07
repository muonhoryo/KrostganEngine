
#include <Engine.h>
#include <ICallbackRec_Upd.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_Upd::ICallbackRec_Upd() {
	ICallbackRec_Upd& ref = *this;
	Engine::GetUpdateModule().Add(ref);
}
ICallbackRec_Upd::~ICallbackRec_Upd() {
	ICallbackRec_Upd& ref = *this;
	Engine::GetUpdateModule().Remove(ref);
}
