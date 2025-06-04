
#include <Engine.h>
#include <ICallbackRec_LUpd.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_LUpd::ICallbackRec_LUpd() {
	Engine::GetLateUpdModule().Add(*this);
}
ICallbackRec_LUpd::~ICallbackRec_LUpd() {
	Engine::GetLateUpdModule().Remove(*this);
}
