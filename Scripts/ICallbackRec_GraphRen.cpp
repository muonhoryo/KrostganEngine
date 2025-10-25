
#include <EngineCore.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphRen::ICallbackRec_GraphRen(byte RendLayer)
	:RendLayer(RendLayer) {

	EngineCallbackHandler<ICallbackRec_GraphRen>& mod = Engine::GetRenderModule();
	mod.Add(*this);
}
ICallbackRec_GraphRen::~ICallbackRec_GraphRen() {

	EngineCallbackHandler<ICallbackRec_GraphRen>& mod = Engine::GetRenderModule();
	mod.Remove(*this);
	cout << "Remove ui graphics from render" << endl;
}

void ICallbackRec_GraphRen::RenderGraphic(RenderWindow& window) {
	if (GetActivity())
		RenderGraphicAction(window);
}

byte ICallbackRec_GraphRen::GetRendLayer() const {
	return RendLayer;
}
bool ICallbackRec_GraphRen::GetActivity() const {
	return IsActive;
}

void ICallbackRec_GraphRen::SetRendLayer(byte layer) {
	RendLayer = layer;
	Engine::GetRenderModule().SetNeedToSort();
}
void ICallbackRec_GraphRen::SetActivity(bool isActive) {
	IsActive = isActive;
}