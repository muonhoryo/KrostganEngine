
#include <Engine.h>
#include <ICallbackRec_Upd.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_Upd::ICallbackRec_Upd() {
	Engine::GetUpdateModule().Add(*this);
}
ICallbackRec_Upd::~ICallbackRec_Upd() {
	Engine::GetUpdateModule().Remove(*this);
}
