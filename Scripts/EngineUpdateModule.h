#pragma once

#include <EngineWorkCycleModule.h>
#include <ICallbackRec_Upd.h>
#include <vector>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {

	class EngineUpdateModule : public EngineWorkCycleModule, public EngineCallbackHandler<ICallbackRec_Upd> {
	public:
		EngineUpdateModule(RenderWindow& Window);

		void Execute() override;

	private:
		RenderWindow& Window;
		Event& UpdateEvent;
		vector<Event> PlayerInput;
		Clock FrameDeltaTimer;

	public:
		void SetFrameDeltaTime(float time);
	};
}