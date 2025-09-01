
#include <EngineCore.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphPostRen::ICallbackRec_GraphPostRen(char RendLayer)
	:RendLayer(RendLayer){

	EngineCallbackHandler<ICallbackRec_GraphPostRen>& mod = Engine::GetRenderModule();
	mod.Add(*this);
}
ICallbackRec_GraphPostRen::~ICallbackRec_GraphPostRen() {

	EngineCallbackHandler<ICallbackRec_GraphPostRen>& mod = Engine::GetRenderModule();
	mod.Remove(*this);
	cout << "Remove ui graphics from render" << endl;
}

char ICallbackRec_GraphPostRen::GetRendLayer() const {
	return RendLayer;
}
void ICallbackRec_GraphPostRen::SetRendLayer(char layer) {
	RendLayer = layer;
	Engine::GetRenderModule().SetNeedToSort();
}