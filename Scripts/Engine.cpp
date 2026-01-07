
#include <EngineCore.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Extensions.h>
#include <SFML/System.hpp>
#include <DBG_DivineCommander.h>
#include <CoreVisual.h>
#include <WarFogStencilGen.h>
#include <WarFogObserversManager.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Visual;

const std::string Engine::ENGINE_VERSION = "A0.6.2.1";

Engine::Engine()
	:RenderModule(*new EngineRenderModule(RendWin)),
	UpdateModule(*new EngineUpdateModule(RendWin)),
	LateUpdateModule(*new EngineLateUpdateModule()),
	PhysicsEng(*new PhysicsEngine()),
	IsFullscreen(false){

	Singleton = this;

	EngineConfigLoad config=EngineConfigLoad();
	EngineConfiguration = &config.LoadEngineConfig();
	GlobalConstsLoad consts = GlobalConstsLoad();
	Consts = &consts.LoadGlobalConsts();
	ExtGlobalResourcesLoad::LoadGlobalResources();

	auto uiDeser=new UserInterfacesDeserializer();
	uiDeser->Deserialize();

	CreateGameWindow();
	SetCameraPos(Vector2f(0, 0));

	CurrMode = nullptr;
	EngStateHandler = EngineStateHandler();

	InitializeSystems();

	ReqToSetStartMode();
}
void Engine::CreateGameWindow(bool isFullScreen) {

	ContextSettings windSetts;
	windSetts.stencilBits = 8;
	string header = "Krostgan Engine " + Engine::ENGINE_VERSION;
	const VideoMode* mode = nullptr;
	Vector2u oldResol = GetScreenSize();
	Uint32 style;
	if (isFullScreen) {
		mode = &VideoMode::getFullscreenModes()[0];
		style = sf::Style::Close | sf::Style::Fullscreen;
	}
	else {
		mode = new VideoMode(Singleton->EngineConfiguration->WindowResolution.x, Singleton->EngineConfiguration->WindowResolution.y);
		style = sf::Style::Close;
	}
	RendWin.create(*mode, header, style, windSetts);
	glewInit();
	SetZoom(Zoom);
	RendWin.setFramerateLimit(EngineConfiguration->FrameRateLimit);
	auto warFogGen = WarFogStencilGen::GetInstance();
	if (warFogGen != nullptr)
		warFogGen->ReinitializeBuffer();
	WindowResizeEvArgs resArgs(oldResol,GetScreenSize());
	ResizeWindowEventHandler.Execute(resArgs);
}
void Engine::InitializeSystems() {
	new PlayerInputManager();
	UserInterfaceManager::Initialize();
	GroupSelectionSystem::GetInstance();
	InitializeCursorManager();
	new WarFogObserversManager();
}
void Engine::InitializeCursorManager() {
	Cursor& def = *new Cursor();
	Cursor& att = *new Cursor();

	def.loadFromSystem(Cursor::Arrow);
	const string& defintion = ExternalGlobalResources::CORE_RES_CURSORTEX_ATTACK;
	auto& tex = ExternalGlobalResources::GetRes_t<ExtGlRes_Texture>(defintion)->Tex;
	Image img_att = tex.copyToImage();
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

void Engine::SetZoom(float zoom) {
	if (zoom <= 0)
		throw exception("Zoom cannot be less or equal 0");
	else {
		auto args = ViewZoomChangedEvArgs(Singleton->Zoom, zoom);
		auto& view = InstanceNewView();
		view.zoom(zoom / Singleton->Zoom);
		Singleton->RendWin.setView(view);
		Singleton->Zoom = zoom;
		SetCameraPos(GetCameraPos());
		ViewZoomChangedEventHandler.Execute(args);
	}
}
void Engine::SetCameraPos(Vector2f pos) {
	auto& view = InstanceNewView();
	auto lvlInfo = LevelManager::GetLevelInfo();

	if (lvlInfo!=nullptr && !DBG_DivineCommander::GetActivity()) {		//Limit camera moving if divine commander is off-line

		const Rect<float>& borders = lvlInfo->CameraBorders;
		Vector2f windSize = (Vector2f)GetScreenSize();
		windSize *= GetZoom();
		windSize *= 0.5f;

		float left = borders.left + windSize.x;
		float top = borders.top + windSize.y;
		float right = borders.left + borders.width - windSize.x;
		float bottom = borders.top + borders.height - windSize.y;

		if (left >= right)
			pos.x = borders.left+borders.width*0.5f;
		else
			pos.x = clamp<float>(pos.x, left, right);

		if (top >= bottom)
			pos.y = borders.top + borders.height* 0.5f;
		else
			pos.y = clamp<float>(pos.y,top ,bottom );
	}
	view.setCenter(pos);
	Singleton->RendWin.setView(view);
}
void Engine::MoveCamera(Vector2f movVal) {
	SetCameraPos(GetCameraPos() + movVal);
}
void Engine::SetFullScreen(bool isFull) {

	if (isFull != IsFullScreenWindow()) {

		Vector2f camPos = GetCameraPos();
		Singleton->CreateGameWindow(isFull);
		Singleton->IsFullscreen = isFull;

		SetCameraPos(camPos);
	}
}
void Engine::UnloadCallbacksModules() {

	GetUpdateModule().Unload();
	GetLateUpdModule().Unload();
	GetRenderModule().Unload();
	GetPhysicsEngine().Unload();
	auto warfog=WarFogStencilGen::GetInstance();
	if (warfog != nullptr)
		warfog->Unload();
}

View& Engine::InstanceNewView() {
	View& view = *new View(Singleton->RendWin.getView());
	return view;
}

RenderWindow& Engine::GetRenderWindow() {
	return Engine::Singleton->RendWin;
}
float Engine::GetFrameDeltaTime() {
	return Singleton->FrameDeltaTime;
}
float Engine::GetFrameRenderTime() {
	return Singleton->FrameRenderTime;
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
bool Engine::IsFullScreenWindow() {
	return Singleton->IsFullscreen;
}
float Engine::GetZoom() {
	return Singleton->Zoom;
}
Vector2f Engine::GetCameraPos() {
	return Singleton->RendWin.getView().getCenter();
}

Vector2f Engine::ScreenPosToGlobalCoord(const Vector2f& screenPos) {
	Vector2f globalCoord = Vector2f(screenPos);
	globalCoord *= GetZoom();
	auto& view = Singleton->RendWin.getView();
	globalCoord +=view.getCenter();
	Vector2f screenSize = (Vector2f)GetScreenSize();
	screenSize *= 0.5f;
	screenSize *= GetZoom();
	globalCoord -= screenSize;
	return globalCoord;
}
Vector2f Engine::GlobalCoordToScreenPos(const Vector2f& globalCoord) {
	Vector2f screenPos = Vector2f(globalCoord);
	auto& view = Singleton->RendWin.getView();
	Vector2f screenSize = (Vector2f)GetScreenSize();
	screenSize *= 0.5f;
	screenSize *= GetZoom();
	Vector2f center = view.getCenter();
	screenPos -= center;
	screenPos += screenSize;
	screenPos /= GetZoom();
	return screenPos;
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
	return mousePos.x >= 0 && mousePos.x <= (int)screenSize.x &&
		mousePos.y>=0 && mousePos.y <= (int)screenSize.y;
}
bool Engine::HasWindowFocus() {
	return Singleton->RendWin.hasFocus();
}