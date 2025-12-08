
#include <EngineCore.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

ICallbackRec_GraphRen::ICallbackRec_GraphRen(std::byte RendLayer)
	:RendLayer(RendLayer) {

	EngineCallbackHandler<ICallbackRec_GraphRen>& mod = Engine::GetRenderModule();
	mod.Add(*this);
}
ICallbackRec_GraphRen::~ICallbackRec_GraphRen() {

	EngineCallbackHandler<ICallbackRec_GraphRen>& mod = Engine::GetRenderModule();
	mod.Remove(*this);
}

void ICallbackRec_GraphRen::RenderGraphic(RenderWindow& window) {
	if (GetActivity())
		RenderGraphicAction(window);
}

std::byte ICallbackRec_GraphRen::GetRendLayer() const {
	return RendLayer;
}
bool ICallbackRec_GraphRen::Get_IsHidenByWarFog() const {
	return IsHidenByWarFog;
}
bool ICallbackRec_GraphRen::Get_IsShownByWarFog() const {
	return IsShownByWarFog;
}
bool ICallbackRec_GraphRen::GetActivity() const {
	return IsActive;
}

void ICallbackRec_GraphRen::SetRendLayer(std::byte layer) {
	RendLayer = layer;
	Engine::GetRenderModule().SetNeedToSort();
}
void ICallbackRec_GraphRen::SetActivity(bool isActive) {
	IsActive = isActive;
}
void ICallbackRec_GraphRen::Set_IsHidenByWarFog(bool isHiden){
	IsHidenByWarFog = isHiden;
	Engine::GetRenderModule().SetNeedToSort();
}
void ICallbackRec_GraphRen::Set_IsShownByWarFog(bool isShown) {
	IsShownByWarFog = isShown;
	Engine::GetRenderModule().SetNeedToSort();
}