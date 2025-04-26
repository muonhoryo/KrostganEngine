
#include <EngineCore.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphRen::ICallbackRec_GraphRen() {
	ICallbackRec_GraphRen* cb = this;
	Engine::GetRenderModule().Add(cb);
}
ICallbackRec_GraphRen::~ICallbackRec_GraphRen() {
	ICallbackRec_GraphRen* cb = this;
	Engine::GetRenderModule().Remove(cb);
	cout << "Remove graphics from render" << endl;
}
