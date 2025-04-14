
#include <EngineCore.h>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace KrostganEngine::Core;


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

void Engine::ReqToSetMode_Game() {
	Engine::RequestToChangeState(EngineState::StateType::Game);
}
void Engine::ReqToSetMode_MainMenu() {
	Engine::RequestToChangeState(EngineState::StateType::MainMenu);
}

void Engine::RequestToChangeState(EngineState::StateType state) {
	if (state != EngState.CurrState) {
		if (!EngState.NeedToInterrupt) {
			EngState.NeedToInterrupt = true;
		}
		if (state != EngState.NextState) {
			EngState.NextState = state;
		}
	}
}
void Engine::SetMode_Game() {
	/*EngState.GameSt = GameMode();
	Engine::EngMode = Engine::EngState.GameSt;*/
}
void Engine::SetMode_MainMenu() {
	/*EngState.MainMenuSt = MainMenuMode();
	Engine::EngMode = &Engine::EngState.MainMenuSt;*/
}
void Engine::ResolveInterruption() {
	switch (EngState.NextState)
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
	EngState.NeedToInterrupt = false;
	EngState.CurrState = EngState.NextState;
}

const std::string Engine::ENGINE_VERSION = "A0.0.1";
Engine* Engine::Singleton = nullptr;

EngineMode* Engine::EngMode = nullptr;
Engine::EngineState Engine::EngState = Engine::EngineState();

float Engine::GetFrameTime() {
	return Engine::Singleton->FrameTime;
}
