
#include <EngineCore.h>
#include <ICallbackRec_GraphRen.h>
#include <vector>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule():EngineWorkCycleModule(),Graphics(*new forward_list<ICallbackRec_GraphRen*>) {
}
void EngineRenderModule::Execute() {
	RenderWindow& window = Engine::GetRenderWindow();
	window.clear();
	for (auto rec : Graphics) {
		(*rec).RenderGraphic(window);
	}
}
void EngineRenderModule::Initialize(forward_list<ICallbackRec_GraphRen*> graphs){
	for (auto gr : graphs) {
		Graphics.push_front(gr);
	}
}
void EngineRenderModule::Remove(const ICallbackRec_GraphRen*& graphToDel) {

	auto itToD = Graphics.cbegin();
	auto it = Graphics.begin();
	for (;it != Graphics.cend();++it) {
		if (*it == graphToDel) {
			break;
		}
		++itToD;
	}
	Graphics.erase_after(itToD);
}
void EngineRenderModule::Add(ICallbackRec_GraphRen*& graphToAdd) {
	Graphics.push_front(graphToAdd);
}