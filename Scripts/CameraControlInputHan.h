#pragma once

#include <PlayerInputManager.h>

namespace KrostganEngine::PlayerControl {

	class CameraControlInputHan : public IBaseInputHandler{
	public:
		CameraControlInputHan();
		virtual ~CameraControlInputHan(){}

		void Update(const CallbackRecArgs_Upd& args) override;
	};
}