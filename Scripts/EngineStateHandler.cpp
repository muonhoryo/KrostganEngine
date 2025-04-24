
#include <EngineCore.h>

using namespace KrostganEngine::Core;

EngineStateHandler::EngineStateHandler() {
	CurrState = EngineState::None;
	NextState = EngineState::None;
	NeedToInterrupt = false;
	GameSt = nullptr;
}
