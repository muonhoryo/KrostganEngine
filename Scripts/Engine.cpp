
#include <EngineCore.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Extensions.h>
#include <SFML/System.hpp>
#include <DivineCommander.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;


Engine::Engine()
	:RenderModule(*new EngineRenderModule(RendWin)),
	UpdateModule(*new EngineUpdateModule(RendWin)),
	LateUpdateModule(*new EngineLateUpdateModule()),
	PhysicsEng(*new PhysicsEngine()){

	Singleton = this;

	EngineConfigLoad config=EngineConfigLoad();
	EngineConfiguration = &config.LoadEngineConfig();
	GlobalConstsLoad consts = GlobalConstsLoad();
	Consts = &consts.LoadGlobalConsts();
	ExtGlobalResourcesLoad resources = ExtGlobalResourcesLoad();
	GlobalResources = &resources.LoadGlobalResources();

	string header = "Krostgan Engine " + Engine::ENGINE_VERSION;
	Vector2f resol = EngineConfiguration->WindowResolution;
	RendWin.create(VideoMode(resol.x,resol.y), header,Style::Close);
	View view;
	view.setCenter(0, 0);
	view.setSize(resol.x, resol.y);
	view.zoom(Zoom);
	RendWin.setView(view);
	RendWin.setFramerateLimit(EngineConfiguration->FrameRateLimit);
	CurrMode = nullptr;
	EngStateHandler = EngineStateHandler();

	GroupSelectionSystem::GetInstance();

	InitializeSystems();

	ReqToSetMode_LevelDeser();
	SetMode_LevelDeser();
	ResetInterruption();
}
void Engine::InitializeSystems() {
	InitializeCursorManager();
}
void Engine::InitializeCursorManager() {
	Cursor& def = *new Cursor();
	Cursor& att = *new Cursor();

	def.loadFromSystem(Cursor::Arrow);
	Image img_att = GlobalResources->CursorSprite_Attack.copyToImage();
	Vector2u hotSpot = EngineConfiguration->CursorHotspot_Attack;
	att.loadFromPixels(img_att.getPixelsPtr(), img_att.getSize(),hotSpot);

	WindCursorManager = new CursorManager(RendWin, def, att);
}


Engine& Engine::GetInstance() {
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

void Engine::SetZoom(float zoom) {
	if (zoom <= 0)
		throw exception("Zoom cannot be less or equal 0");
	else {
		auto& view = InstanceNewView();
		view.zoom(zoom / Singleton->Zoom);
		Singleton->RendWin.setView(view);
		Singleton->Zoom = zoom;
	}
}
void Engine::SetCameraPos(Vector2f pos) {
	const Rect<float>& borders = Singleton->EngineConfiguration->CameraMovingArea;
	auto& view = InstanceNewView();

	if (!DivineCommander::GetActivity()) {		//Limit camera moving if divine commander is off-line

		pos.x = clamp<float>(pos.x, borders.left, borders.left + borders.width);
		pos.y = clamp<float>(pos.y, borders.top, borders.top + borders.height);
	}
	view.setCenter(pos);
	Singleton->RendWin.setView(view);
}
void Engine::MoveCamera(Vector2f movVal) {
	SetCameraPos(GetCameraPos() + movVal);
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

const std::string Engine::ENGINE_VERSION = "A0.1.0.0";


RenderWindow& Engine::GetRenderWindow() {
	return Engine::Singleton->RendWin;
}
float Engine::GetFrameDeltaTime() {
	return Singleton->FrameDeltaTime;
}
float Engine::GetFrameRenderTime() {
	return Singleton->FrameRenderTime;
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
EngineLateUpdateModule& Engine::GetLateUpdModule() {
	return Singleton->LateUpdateModule;
}
PhysicsEngine& Engine::GetPhysicsEngine() {
	return Singleton->PhysicsEng;
}
CursorManager& Engine::GetCursorManager() {
	return *Singleton->WindCursorManager;
}
const EngineConfig& Engine::GetEngineConfig() {
	return *(Singleton->EngineConfiguration);
}
const GlobalConsts& Engine::GetGlobalConsts() {
	return *Singleton->Consts;
}
const ExternalGlobalResources& Engine::GetGlobalResources() {
	return *Singleton->GlobalResources;
}
float Engine::GetZoom() {
	return Singleton->Zoom;
}
Vector2f Engine::GetCameraPos() {
	return Singleton->RendWin.getView().getCenter();
}

Vector2f Engine::ScreenPosToGlobalCoord(const Vector2f& screenPos) {
	Vector2f globalCoord = Vector2f(screenPos);
	auto& view = Singleton->RendWin.getView();
	globalCoord +=view.getCenter();
	Vector2f screenSize = (Vector2f)GetScreenSize();
	screenSize.x *= 0.5;
	screenSize.y *= 0.5;
	globalCoord -= screenSize;
	globalCoord *= GetZoom();
	return globalCoord;
}
Vector2u Engine::GetScreenSize() {
	return Singleton->RendWin.getSize();
}
Vector2f Engine::GetCursorClampedPos() {
	Vector2i cursorPos = Mouse::getPosition(Engine::GetRenderWindow());
	Vector2u screenSize = Engine::GetScreenSize();
	Vector2f globalPos = Vector2f(
		clamp<float>((float)cursorPos.x, 0, (float)screenSize.x),
		clamp<float>((float)cursorPos.y, 0, (float)screenSize.y));
	return globalPos;
}
bool Engine::IsMouseOnScreen() {
	return IsMouseOnScreen(Mouse::getPosition(Engine::GetRenderWindow()));
}
bool Engine::IsMouseOnScreen(Vector2i mousePos) {
	Vector2u screenSize = Engine::GetScreenSize();
	return mousePos.x > 0 && mousePos.x < (int)screenSize.x &&
		mousePos.y>0 && mousePos.y < (int)screenSize.y;
}
bool Engine::HasWindowFocus() {
	return Singleton->RendWin.hasFocus();
}