
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineCore.h>

using namespace KrostganEngine::Core;
using namespace sf;

EngineUpdateModule::EngineUpdateModule(RenderWindow& Window):EngineCallbackHandler<ICallbackRec_Upd>(),
Window(Window),UpdateEvent(*new Event) {
	PlayerInput = vector<Event>();
}
void EngineUpdateModule::Execute() {
	SetFrameDeltaTime(FrameDeltaTimer.restart().asSeconds());
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
	CallbackRecArgs_Upd args = CallbackRecArgs_Upd(PlayerInput,Engine::GetFrameDeltaTime());

	IsIteratingCallbacks = true;

	for (auto scr : Callbacks) {
		
		if (scr == nullptr)
			continue;

		scr->Update(args);
		if (Engine::IsNeedToInterrupt())
			return;

	}
	IsIteratingCallbacks = false;
	DeleteDelayedCallbacks();
}

void EngineUpdateModule::SetFrameDeltaTime(float time) {
	Engine::Singleton->FrameDeltaTime = time;
}