
#include <PlayerInputManager.h>
#include <Engine.h>
#include <CollectionsExts.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine;
using namespace sf;

IBaseInputHandler::IBaseInputHandler()
	:IPlayerInputHandler(){

	PlayerInputManager::Instance->AddInputHandler(*this);
}
IBaseInputHandler::~IBaseInputHandler() {
	PlayerInputManager::Instance->RemoveInputHandler(*this);
}

IPriorityInputHandler::~IPriorityInputHandler() {
	
	auto& inst = *PlayerInputManager::Instance;
	if (inst.PriorityInputHan == this)
		AbortHandling();
}



void IPriorityInputHandler::StartHandling() {

	StartHandling_Action();
	auto& inst = *PlayerInputManager::Instance;
	inst.AddPriorityInputHan(*this);
}
void IPriorityInputHandler::AbortHandling() {
	
	AbortHandling_Action();
	auto& inst = *PlayerInputManager::Instance;
	inst.RemovePriorityInputHan(*this);
}


IWindowInputHandler::IWindowInputHandler()
	:IPlayerInputHandler() {

	PlayerInputManager::Instance->AddWindInputHandler(*this);
}
IWindowInputHandler::~IWindowInputHandler() {
	PlayerInputManager::Instance->RemoveWindInputHandler(*this);
}



PlayerInputManager::PlayerInputManager()
	:ICallbackRec_Upd(){

	if (Instance != nullptr)
		throw exception("PlayerInputManager is already instantiated");

	Instance = this;
}
PlayerInputManager::~PlayerInputManager() {

	Instance = nullptr;
}
void PlayerInputManager::AddInputHandler(IBaseInputHandler& handler) {
	InputHandlers.push_back(&handler);
}
void PlayerInputManager::RemoveInputHandler(IBaseInputHandler& handler) {
	CollectionsExts::Remove(InputHandlers, &handler);
}
void PlayerInputManager::AddPriorityInputHan(IPriorityInputHandler& handler) {

	if (PriorityInputHan != nullptr)
		throw exception("Trying to add new priority input handler while the same is active");

	PriorityInputHan = &handler;
}
void PlayerInputManager::RemovePriorityInputHan(IPriorityInputHandler& handler) {

	if (PriorityInputHan != &handler)
		throw exception("Current priority input handler is not this script");

	PriorityInputHan = nullptr;
}
void PlayerInputManager::AddWindInputHandler(IWindowInputHandler& handler) {
	WindInputHandlers.push_back(&handler);
}
void PlayerInputManager::RemoveWindInputHandler(IWindowInputHandler& handler) {
	CollectionsExts::Remove(WindInputHandlers, &handler);
}


void PlayerInputManager::Update(CallbackRecArgs_Upd args) {

	for (auto& inp : args.PlayerInput) {
		if (inp.type == Event::KeyPressed) {

			if (inp.key.shift/*inp.key.code == Keyboard::Key::LShift || inp.key.code == Keyboard::Key::RShift*/) {

				IsPressed_Shift = true;
			}
			if (inp.key.alt/*inp.key.code == Keyboard::Key::LAlt || inp.key.code == Keyboard::Key::RAlt*/) {

				IsPressed_Alt = true;
			}
			if (inp.key.control/*inp.key.code == Keyboard::Key::LControl || inp.key.code == Keyboard::Key::RControl*/) {

				IsPressed_Ctrl = true;
			}
		}
		else if (inp.type == Event::KeyReleased) {

			if (!inp.key.shift/*inp.key.code == Keyboard::Key::LShift || inp.key.code == Keyboard::Key::RShift*/) {

				IsPressed_Shift = false;
			}
			if (!inp.key.alt/*inp.key.code == Keyboard::Key::LAlt || inp.key.code == Keyboard::Key::RAlt*/) {

				IsPressed_Alt = false;
			}
			if (!inp.key.control/*inp.key.code == Keyboard::Key::LControl || inp.key.code == Keyboard::Key::RControl*/){

				IsPressed_Ctrl = false;
			}
		}
	}

	if (PriorityInputHan == nullptr) {

		for (auto han : InputHandlers) {
			han->Update(args);
		}
	}
	else {
		PriorityInputHan->Update(args);
	}

	for (auto han : WindInputHandlers) {
		han->Update(args);
	}
}

void PlayerInputManager::Clear() {
	
	if (Instance->PriorityInputHan != nullptr)
		delete Instance->PriorityInputHan;

	for (auto han : Instance->InputHandlers)
		delete han;

	for (auto han : Instance->WindInputHandlers)
		delete han;

	Instance->InputHandlers.clear();
	Instance->WindInputHandlers.clear();
}

//
//
// Static
//
//

const PlayerInputManager& PlayerInputManager::GetInstance() {
	return *Instance;
}
bool PlayerInputManager::GetBtnState_Escape() {

	if (FreeBtn_Escape) {

		float time = ReservBtnDelay_Escape.getElapsedTime().asSeconds();
		float reqTime = Engine::GetGlobalConsts().EscapeBtn_PressDelay;
		if (time >= reqTime) {
			IsReservedBtn_Escape = false;
			FreeBtn_Escape = false;
			return false;
		}
		else
			return true;
	}
	else
		return IsReservedBtn_Escape;
}
void PlayerInputManager::SetBtnState_Escape(bool newState) {
	if (newState != IsReservedBtn_Escape) {

		if (!newState) {
			ReservBtnDelay_Escape.restart();
			FreeBtn_Escape = true;
		}
		else {
			IsReservedBtn_Escape = true;
		}
	}
}

/// <summary>
/// Return true if shift-button is pressed
/// </summary>
/// <returns></returns>
bool PlayerInputManager::GetBtnState_Shift() {
	return IsPressed_Shift;
}
/// <summary>
/// Return true if alt-button is pressed
/// </summary>
/// <returns></returns>
bool PlayerInputManager::GetBtnState_Alt() {
	return IsPressed_Alt;
}
/// <summary>
/// Return true if ctrl-button is pressed
/// </summary>
/// <returns></returns>
bool PlayerInputManager::GetBtnState_Ctrl() {
	return IsPressed_Ctrl;
}