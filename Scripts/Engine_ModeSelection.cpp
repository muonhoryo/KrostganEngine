
#include <Engine.h>

using namespace KrostganEngine;

void Engine::ReqToSetStartMode() {

	ReqToSetMode_MainMenu();
	SetMode_MainMenu();
	/*ReqToSetMode_StartMsg();
	SetMode_StartMsg();*/
	ResetInterruption();
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
//void Engine::ReqToSetMode_StartMsg() {
//	Engine::RequestToChangeState(EngineState::StartMessage);
//}

bool Engine::IsNeedToInterrupt() {
	return Singleton->EngStateHandler.NeedToInterrupt;
}
EngineState Engine::GetCurrentEngState() {
	return Singleton->EngStateHandler.CurrState;
}
EngineState Engine::GetNextEngState() {
	return Singleton->EngStateHandler.NextState;
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
	delete Singleton->CurrMode;
	Singleton->EngStateHandler.GameSt = new GameMode();
	Singleton->CurrMode = Singleton->EngStateHandler.GameSt;
}
void Engine::SetMode_MainMenu() {
	delete Singleton->CurrMode;
	Singleton->EngStateHandler.MainMenuSt = new MainMenuMode();
	Singleton->CurrMode = Singleton->EngStateHandler.MainMenuSt;
}
void Engine::SetMode_LevelDeser() {
	delete Singleton->CurrMode;
	Singleton->EngStateHandler.LevelDeserSt = new LevelDeserializationMode();
	Singleton->CurrMode = Singleton->EngStateHandler.LevelDeserSt;
}
//void Engine::SetMode_StartMsg() {
//	delete Singleton->CurrMode;
//	Singleton->EngStateHandler.StartMsgSt = new StartMessageMode();
//	Singleton->CurrMode = Singleton->EngStateHandler.StartMsgSt;
//}

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
	/*case EngineState::StartMessage:
		Engine::SetMode_StartMsg();
		break;*/
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