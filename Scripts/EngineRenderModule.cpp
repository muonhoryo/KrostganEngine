
#include <EngineCore.h>
#include <ICallbackRec_GraphRen.h>
#include <vector>
#include <Extensions.h>

using namespace std;
using namespace KrostganEngine::Core;

EngineRenderModule::EngineRenderModule(RenderWindow& Window):EngineWorkCycleModule(),
Graphics(*new forward_list<ICallbackRec_GraphRen*>),Window(Window)
{
}
void EngineRenderModule::Execute() {
	if (!Window.isOpen())
		return;
	Window.clear();
	for (auto rec : Graphics) {
		(*rec).RenderGraphic(Window);
	}
	Window.display();
}
void EngineRenderModule::Initialize(forward_list<ICallbackRec_GraphRen*> graphs){
	Unload();
	for (auto gr : graphs) {
		Graphics.push_front(gr);
	}
}
void EngineRenderModule::Unload() {
	Graphics.clear();
}
void EngineRenderModule::Remove( ICallbackRec_GraphRen * const& graphToDel) {

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