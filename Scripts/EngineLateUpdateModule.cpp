
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
	for (auto scr : Callbacks) {
		scr->Update(args);
		if (Engine::IsNeedToInterrupt())
			return;
	}
}