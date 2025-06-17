
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <EngineCore.h>

using namespace KrostganEngine::Core;
using namespace sf;

EngineLateUpdateModule::EngineLateUpdateModule() :EngineCallbackHandler<ICallbackRec_LUpd>()
{
}
void EngineLateUpdateModule::Execute() {

	CallbackRecArgs_LUpd args = CallbackRecArgs_LUpd();
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