
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
	for (auto rec : EngineCallbackHandler<ICallbackRec_GraphRen>::Callbacks) {
		(*rec).RenderGraphic(Window);
	}
	for (auto rec : EngineCallbackHandler<ICallbackRec_GraphPostRen>::Callbacks) {
		(*rec).RenderGraphic(Window);
	}
	Window.display();
	SetFrameRenderTime(FrameRenderTime.getElapsedTime().asSeconds());
}

void EngineRenderModule::SetFrameRenderTime(float time) {
	Engine::Singleton->FrameRenderTime = time;
}