
#include <BaseAppInputHandler.h>
#include <Engine.h>
#include <Extensions.h>
#include <ConsoleCommsInterpretator.h>
#include <EngineCore.h>
#include <Debug.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::PlayerControl;

BaseAppInputHandler::BaseAppInputHandler()
	:IWindowInputHandler() {

}

void BaseAppInputHandler::Update(const CallbackRecArgs_Upd& args) {

	for (auto& input : args.PlayerInput) {

		if (input.type == Event::KeyPressed) {

			if (!DbgConsoleInputHandler::GetDbgConsoleStats() &&
				input.key.code == Keyboard::Tilde) { //Open console

				auto dbgConsHan=new DbgConsoleInputHandler();
				dbgConsHan->StartHandling();
				return;
			}
			else if (input.key.code == Keyboard::F3) {

				//if (PlayerInputManager::GetBtnState_Escape()) {
				//	continue;
				//}

				Engine::GetRenderWindow().close();
				exit(0);
			}
			else if (input.key.code == Keyboard::F5) {
				Engine::SetFullScreen(!Engine::IsFullScreenWindow());
			}
		}
	}
}