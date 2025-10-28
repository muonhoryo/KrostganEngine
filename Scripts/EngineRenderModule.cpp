
#include <EngineCore.h>
#include <vector>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule(RenderWindow& Window): EngineCallbackHandler<ICallbackRec_GraphRen>(),
	Window(Window)
{
}
void EngineRenderModule::Execute() {
	FrameRenderTime.restart();
	if (!Window.isOpen())
		return;
	Window.clear();
	IsIteratingCallbacks = true;
	for (auto rec : Callbacks) {

		if (rec == nullptr)
			continue;

		rec->RenderGraphic(Window);
	}
	IsIteratingCallbacks = false;
	DeleteDelayedCallbacks();
	if (NeedToSort) {

		Callbacks.sort(RenCallbks_SortPred);
		NeedToSort = false;
	}
	Window.display();
	SetFrameRenderTime(FrameRenderTime.getElapsedTime().asSeconds());
}

void EngineRenderModule::SetFrameRenderTime(float time) {
	Engine::Singleton->FrameRenderTime = time;
}
void EngineRenderModule::SetNeedToSort() {
	NeedToSort = true;
}

void EngineRenderModule::Add(ICallbackRec_GraphRen& callbck) {
	EngineCallbackHandler<ICallbackRec_GraphRen>::Add(callbck);
	NeedToSort = true;
}