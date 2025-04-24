
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineWorkCycleModule.h>
#include <Engine.h>

using namespace KrostganEngine::Core;
using namespace sf;

EngineUpdateModule::EngineUpdateModule(RenderWindow& Window):EngineCallbackHandler<ICallbackRec_Upd>(),
Window(Window),UpdateEvent(*new Event) {
	PlayerInput = vector<Event>();
}
void EngineUpdateModule::Execute() {
	PlayerInput.clear();
	if (Window.isOpen()) {
		while (Window.pollEvent(UpdateEvent))
		{
			if (UpdateEvent.type == Event::Closed)
			{
				Window.close();
				exit(1);
			}
			PlayerInput.push_back(UpdateEvent);
		}
	}
	CallbackRecArgs_Upd args = CallbackRecArgs_Upd(PlayerInput);
	for (auto scr : Callbacks) {
		scr->Update(args);
		if (Engine::IsNeedToInterrupt())
			return;
	}
}