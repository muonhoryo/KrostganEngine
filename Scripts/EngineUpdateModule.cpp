
#include <EngineWorkCycleModule.h>
#include <Engine.h>

using namespace KrostganEngine::Core;

EngineUpdateModule::EngineUpdateModule(RenderWindow& Window):EngineWorkCycleModule(),
Window(Window),UpdateEvent(*new Event),UpdateScripts(*new forward_list<ICallbackRec_Upd*>) {
}
void EngineUpdateModule::Execute() {
	CallbackRecArgs_Upd args = CallbackRecArgs_Upd(Window, UpdateEvent);
	for (auto scr : UpdateScripts) {
		scr->Update(args);
		if (Engine::IsNeedToInterrupt())
			return;
	}
}
void EngineUpdateModule::Initialize(forward_list<ICallbackRec_Upd*> scrs) {
	Unload();
	for (auto gr : scrs) {
		UpdateScripts.push_front(gr);
	}
}
void EngineUpdateModule::Unload() {
	UpdateScripts.clear();
}
void EngineUpdateModule::Remove(ICallbackRec_Upd * const& scrToDel) {
	auto itToD = UpdateScripts.cbegin();
	auto it = UpdateScripts.begin();
	for (;it != UpdateScripts.cend();++it) {
		if (*it == scrToDel) {
			break;
		}
		++itToD;
	}
	UpdateScripts.erase_after(itToD);
}
void EngineUpdateModule::Add(ICallbackRec_Upd*& scrToDel) {
	UpdateScripts.push_front(scrToDel);
}