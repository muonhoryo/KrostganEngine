
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
	CurrMode = nullptr;
	EngStateHandler = EngineStateHandler();

	ReqToSetMode_Game();
	SetMode_Game();
}


Engine& Engine::GetInstanceEngine() {
	if(Engine::Singleton==nullptr)
		Engine::Singleton = new Engine();
	return *Engine::Singleton;
}
void Engine::StartEngine() {
	while (true) {
		GetCurrentEngMode()->ExecuteCycle();
		if (IsNeedToInterrupt()) {
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
	if (state != GetCurrentEngState()) {
		if (!IsNeedToInterrupt()) {
			Singleton->EngStateHandler.NeedToInterrupt = true;
		}
		if (state != GetNextEngState()) {
			Singleton->EngStateHandler.NextState = state;
		}
	}
}
void Engine::SetMode_Game() {
	Singleton->EngStateHandler.GameSt = new GameMode();
	Singleton->CurrMode = Singleton->EngStateHandler.GameSt;
}
void Engine::SetMode_MainMenu() {
	/*EngState.MainMenuSt = MainMenuMode();
	Engine::EngMode = &Engine::EngState.MainMenuSt;*/
}
void Engine::ResolveInterruption() {
	switch (Singleton->EngStateHandler.NextState)
	{
	case KrostganEngine::Core::EngineState::None:
		break;
	case KrostganEngine::Core::EngineState::MainMenu:
		Engine::SetMode_Game();
		break;
	case KrostganEngine::Core::EngineState::Game:
		Engine::SetMode_MainMenu();
		break;
	default:
		break;
	}
	Singleton->EngStateHandler.NeedToInterrupt = false;
	Singleton->EngStateHandler.CurrState = GetNextEngState();
}

EngineMode* Engine::GetCurrentEngMode() {
	return Singleton->CurrMode;
}

const std::string Engine::ENGINE_VERSION = "A0.0.3";
Engine* Engine::Singleton = nullptr;

float Engine::GetFrameTime() {
	return Engine::Singleton->FrameTime;
}
RenderWindow& Engine::GetRenderWindow() {
	return Engine::Singleton->RendWin;
}
bool Engine::IsNeedToInterrupt() {
	return Singleton->EngStateHandler.NeedToInterrupt;
}
EngineState Engine::GetCurrentEngState() {
	return Singleton->EngStateHandler.CurrState;
}
EngineState Engine::GetNextEngState() {
	return Singleton->EngStateHandler.NextState;
}
