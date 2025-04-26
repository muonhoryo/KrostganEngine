
#include <EngineCore.h>
#include <vector>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule(RenderWindow& Window):EngineCallbackHandler(),Window(Window)
{
}
void EngineRenderModule::Execute() {
	if (!Window.isOpen())
		return;
	Window.clear();
	for (auto rec : Callbacks) {
		(*rec).RenderGraphic(Window);
	}
	Window.display();
}