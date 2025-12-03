
#include <MainMenuTransitionHandler.h>
#include <Engine.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::Core;

void MainMenuTransitionHandler::Update(const CallbackRecArgs_Upd& args) {

	if (!HasPressed) {

		for (auto& input : args.PlayerInput) {

			if (input.type == Event::KeyPressed &&
				input.key.code == Keyboard::Enter) {

				auto loadTxt = UserInterfaceManager::GetRoot().GetUIElementByName("LoadTxt");
				if (loadTxt != nullptr) {
					loadTxt->SetActivity(true);
				}
				Engine::ReqToSetMode_LevelDeser();

				HasPressed = true;

				break;
			}
		}
	}
}
