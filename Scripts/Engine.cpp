
#include <EngineCore.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <EngineWorkCycleModule.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace std;


Engine::Engine():RenderModule(*new EngineRenderModule(RendWin)),
UpdateModule(*new EngineUpdateModule(RendWin)){
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
	RendWin.create(VideoMode(XRes,YRes), header,Style::Close);
	View view;
	view.setCenter(XRes / 2, YRes / 2);
	view.setSize(XRes, YRes);
	view.zoom(Zoom);
	RendWin.setView(view);
	SetZoom(1.5);
	SetZoom(1);
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
View& Engine::InstanceNewView() {
	View& view = *new View(Singleton->RendWin.getView());
	return view;
}

const std::string Engine::ENGINE_VERSION = "A0.0.9";
Engine* Engine::Singleton = nullptr;

void Engine::SetZoom(float zoom) {
	if (zoom<= 0)
		throw exception("Zoom cannot be less or equal 0");
	else {
		auto& view = InstanceNewView();
		view.zoom(zoom/Singleton->Zoom);
		Singleton->RendWin.setView(view);
		Singleton->Zoom = zoom;
	}
}

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
EngineUpdateModule& Engine::GetUpdateModule() {
	return Singleton->UpdateModule;
}
float Engine::GetZoom() {
	return Singleton->Zoom;
}
