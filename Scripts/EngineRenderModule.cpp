
#include <EngineCore.h>
#include <ICallbackRec_GraphRen.h>
#include <vector>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule():EngineWorkCycleModule() {
	Graphics = vector<ICallbackRec_GraphRen*>();
}
void EngineRenderModule::Execute() {
	RenderWindow& window = Engine::GetRenderWindow();
	window.clear();
	for (auto rec : Graphics) {
		(*rec).RenderGraphic(window);
	}
}
void EngineRenderModule::Initialize(vector<ICallbackRec_GraphRen*> graphs) {
	Graphics = graphs;
}
void EngineRenderModule::Remove(const ICallbackRec_GraphRen*& graphToDel) {
	auto delIt = find(begin(Graphics), end(Graphics), graphToDel);
	Graphics.erase(delIt);
}
void EngineRenderModule::Add(ICallbackRec_GraphRen*& graphToAdd) {
	Graphics.push_back(graphToAdd);
}