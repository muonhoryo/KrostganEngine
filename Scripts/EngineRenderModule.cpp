
#include <EngineCore.h>
#include <vector>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule(RenderWindow& Window): EngineCallbackHandler<ICallbackRec_GraphRen>(), EngineCallbackHandler<ICallbackRec_GraphPostRen>(),
	Window(Window)
{
}
void EngineRenderModule::Execute() {
	FrameRenderTime.restart();
	if (!Window.isOpen())
		return;
	Window.clear();
	EngineCallbackHandler<ICallbackRec_GraphRen>::IsIteratingCallbacks = true;
	EngineCallbackHandler<ICallbackRec_GraphPostRen>::IsIteratingCallbacks = true;
	for (auto rec : EngineCallbackHandler<ICallbackRec_GraphRen>::Callbacks) {

		if (rec == nullptr)
			continue;

		rec->RenderGraphic(Window);
	}
	for (auto rec : EngineCallbackHandler<ICallbackRec_GraphPostRen>::Callbacks) {

		if (rec == nullptr)
			continue;

		rec->RenderGraphic(Window);
	}
	EngineCallbackHandler<ICallbackRec_GraphRen>::IsIteratingCallbacks = false;
	EngineCallbackHandler<ICallbackRec_GraphPostRen>::IsIteratingCallbacks = false;
	EngineCallbackHandler<ICallbackRec_GraphRen>::DeleteDelayedCallbacks();
	EngineCallbackHandler<ICallbackRec_GraphPostRen>::DeleteDelayedCallbacks();
	Window.display();
	SetFrameRenderTime(FrameRenderTime.getElapsedTime().asSeconds());
}

void EngineRenderModule::SetFrameRenderTime(float time) {
	Engine::Singleton->FrameRenderTime = time;
}