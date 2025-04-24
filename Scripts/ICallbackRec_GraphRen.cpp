

#include <ICallbackRec_GraphRen.h>
#include <EngineCore.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphRen::ICallbackRec_GraphRen() {
	ICallbackRec_GraphRen* cb = this;
	Engine::GetRenderModule().Add(cb);
}
ICallbackRec_GraphRen::~ICallbackRec_GraphRen() {
	ICallbackRec_GraphRen* cb = this;
	Engine::GetRenderModule().Remove(cb);
}
