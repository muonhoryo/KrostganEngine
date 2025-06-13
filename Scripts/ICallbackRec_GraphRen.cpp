
#include <EngineCore.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphRen::ICallbackRec_GraphRen() {

	EngineCallbackHandler<ICallbackRec_GraphRen>& mod = Engine::GetRenderModule();
	mod.Add(*this);
}
ICallbackRec_GraphRen::~ICallbackRec_GraphRen() {

	EngineCallbackHandler<ICallbackRec_GraphRen>& mod = Engine::GetRenderModule();
	mod.Remove(*this);
	cout << "Remove graphics from render" << endl;
}
