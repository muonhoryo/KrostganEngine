
#include <MainMenuTransitionHandler.h>
#include <Engine.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::Core;

void MainMenuTransitionHandler::Update(const CallbackRecArgs_Upd& args) {

	if (HasPressed) {

		Engine::ReqToSetMode_LevelDeser();
	}
	else {
		for (auto& input : args.PlayerInput) {

			if (input.type == Event::KeyPressed &&
				input.key.code == Keyboard::Enter) {

				UserInterfaceLoader::Load_LevelDeserialization();

				HasPressed = true;

				break;
			}
		}
	}
}
