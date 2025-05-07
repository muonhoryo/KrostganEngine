
#include <EngineCore.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphRen::ICallbackRec_GraphRen() {
	Engine::GetRenderModule().Add(*this);
}
ICallbackRec_GraphRen::~ICallbackRec_GraphRen() {
	Engine::GetRenderModule().Remove(*this);
	cout << "Remove graphics from render" << endl;
}
