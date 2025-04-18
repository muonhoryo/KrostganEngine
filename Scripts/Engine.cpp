
#include <EngineCore.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <EngineWorkCycleModule.h>

using namespace sf;
using namespace KrostganEngine::Core;


Engine::Engine():RenderModule(*new EngineRenderModule()) {
	Singleton = this;
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

	InitializeSystems();

	ReqToSetMode_LevelDeser();
	SetMode_LevelDeser();
	ResetInterruption();
}
void Engine::InitializeSystems() {

}


Engine& Engine::GetInstanceEngine() {
	if(Engine::Singleton==nullptr)
		new Engine();
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
void Engine::ReqToSetMode_LevelDeser() {
	Engine::RequestToChangeState(EngineState::LevelDeserialization);
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
	Singleton->EngStateHandler.MainMenuSt = new MainMenuMode();
	Singleton->CurrMode = Singleton->EngStateHandler.MainMenuSt;
}
void Engine::SetMode_LevelDeser() {
	Singleton->EngStateHandler.LevelDeserSt = new LevelDeserializationMode();
	Singleton->CurrMode = Singleton->EngStateHandler.LevelDeserSt;
}
void Engine::ResolveInterruption() {
	switch (Singleton->EngStateHandler.NextState)
	{
	case KrostganEngine::Core::EngineState::None:
		break;
	case KrostganEngine::Core::EngineState::MainMenu:
		Engine::SetMode_MainMenu();
		break;
	case KrostganEngine::Core::EngineState::Game:
		Engine::SetMode_Game();
		break;
	case EngineState::LevelDeserialization:
		Engine::SetMode_LevelDeser();
		break;
	default:
		break;
	}
	ResetInterruption();
}
void Engine::ResetInterruption() {
	Singleton->EngStateHandler.NeedToInterrupt = false;
	Singleton->EngStateHandler.CurrState = GetNextEngState();
}

EngineMode* Engine::GetCurrentEngMode() {
	return Singleton->CurrMode;
}

const std::string Engine::ENGINE_VERSION = "A0.0.6";
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
EngineRenderModule& Engine::GetRenderModule() {
	return Singleton->RenderModule;
}
