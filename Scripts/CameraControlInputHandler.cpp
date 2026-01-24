
#include <CameraControlInputHan.h>
#include <Engine.h>
#include <Extensions.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::PlayerControl;

CameraControlInputHan::CameraControlInputHan()
	:IBaseInputHandler(){

}

void CameraControlInputHan::Update(const CallbackRecArgs_Upd& args) {

	if (Engine::IsMouseOnScreen() && Engine::HasWindowFocus())
	{
		Vector2f curPos = Engine::GetCursorClampedPos();
		float trigger = Engine::GetGlobalConsts().CameraMovTriggerArea;
		Vector2u scrSize = Engine::GetScreenSize();
		Vector2i cameraMov = Vector2i(
			curPos.x < trigger ? -1 : (float)scrSize.x - curPos.x <= trigger ? 1 : 0,
			curPos.y < trigger ? -1 : (float)scrSize.y - curPos.y <= trigger ? 1 : 0);

		if (cameraMov != VECTOR2_INT_ZERO) {

			float movStep = Engine::GetPlayerCtrlSettings().CameraMoveSpeed;
			Vector2f movVect = Vector2f(cameraMov.x * movStep, cameraMov.y * movStep);
			Engine::MoveCamera(movVect);
		}
	}
}