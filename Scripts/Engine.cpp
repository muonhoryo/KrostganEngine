
#include <EngineCore.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace KrostganEngine::Core;

enum Engine::EngineState {
	None,
	MainMenu,
	Game
};
struct Engine::EngineStateHandler {
	EngineStateHandler() {
		CurrState = EngineState::None;
		NextState = EngineState::None;
		NeedToInterrupt = false;
	}

	EngineState CurrState = EngineState::None;
	EngineState NextState = EngineState::None;
	bool NeedToInterrupt = false;

	union {

		KrostganEngine::Core::MainMenuMode* MainMenuSt;
		KrostganEngine::Core::GameMode* GameSt;
	};
};

Engine::Engine() {
	GameConfigLoad config=GameConfigLoad();
	string line = string();
	if (!config.GetConfigValue(GameConfigsList::X_WINDOW_RESOLUTION, &line))
		throw exception("Cannot parse window's XResolution");
	unsigned int XRes = stoi(line);
	if (!config.GetConfigValue(GameConfigsList::Y_WINDOW_RESOLUTION, &line))
		throw exception("Cannot parse window's YResolution");
	unsigned int YRes=stoi(line);
	string header = "Krostgan Engine " + Engine::ENGINE_VERSION;
	RendWin.create(VideoMode(XRes,YRes), header);

	ReqToSetMode_Game();
	SetMode_Game();
}

RenderWindow& Engine::GetRenderWindow() {
	return Engine::Singleton->RendWin;
}

Engine& Engine::GetInstanceEngine() {
	if(Engine::Singleton==nullptr)
		Engine::Singleton = new Engine();
	return *Engine::Singleton;
}
void Engine::StartEngine() {
	while (true) {
		CurrMode->ExecuteCycle();
		if (EngStateHandler.NeedToInterrupt) {
			ResolveInterruption();
		}
	}
}

void Engine::ReqToSetMode_Game() {
	Engine::RequestToChangeState(EngineState::Game);
}
void Engine::ReqToSetMode_MainMenu() {
	Engine::RequestToChangeState(EngineState::MainMenu);
}

void Engine::RequestToChangeState(EngineState state) {
	if (state != EngStateHandler.CurrState) {
		if (!EngStateHandler.NeedToInterrupt) {
			EngStateHandler.NeedToInterrupt = true;
		}
		if (state != EngStateHandler.NextState) {
			EngStateHandler.NextState = state;
		}
	}
}
void Engine::SetMode_Game() {
	EngStateHandler.GameSt = new GameMode();
	CurrMode = EngStateHandler.GameSt;
}
void Engine::SetMode_MainMenu() {
	/*EngState.MainMenuSt = MainMenuMode();
	Engine::EngMode = &Engine::EngState.MainMenuSt;*/
}
void Engine::ResolveInterruption() {
	switch (EngStateHandler.NextState)
	{
	case KrostganEngine::Core::Engine::EngineState::None:
		break;
	case KrostganEngine::Core::Engine::EngineState::MainMenu:
		Engine::SetMode_Game();
		break;
	case KrostganEngine::Core::Engine::EngineState::Game:
		Engine::SetMode_MainMenu();
		break;
	default:
		break;
	}
	EngStateHandler.NeedToInterrupt = false;
	EngStateHandler.CurrState = EngStateHandler.NextState;
}

const std::string Engine::ENGINE_VERSION = "A0.0.1";
Engine* Engine::Singleton = nullptr;

EngineMode* Engine::CurrMode = nullptr;
Engine::EngineStateHandler Engine::EngStateHandler = Engine::EngineStateHandler();

float Engine::GetFrameTime() {
	return Engine::Singleton->FrameTime;
}
