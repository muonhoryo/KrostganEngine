
#include <LoseScript.h>
#include <Engine.h>

using namespace KrostganEngine::GameTransitions;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

LoseScript::LoseScript()
	:TransitTime(Engine::GetGlobalConsts().LoseMsg_TransitTime),
	MessageAppearingTime(Engine::GetGlobalConsts().LoseMsg_AppearingTime),
	MessageShowingTime(Engine::GetGlobalConsts().LoseMsg_ShowingTime),
	MessageAppearingDeltaTime(MessageShowingTime - MessageAppearingTime) {

	EntitiesCtrlInputHandler::GetInstance()->TurnOff();
	LostTimer.restart(); 
}

void LoseScript::RenderGraphic(RenderWindow& window) {

	float time = LostTimer.getElapsedTime().asSeconds();
	switch (Stage)
	{
	case KrostganEngine::GameTransitions::LoseScript::LoseMessageStage::Hide:
	{
		if (time >= MessageAppearingTime) {

			Message = new UIText(
				nullptr,
				"You are dead",
				50u,
				DEFAULT_POSITION,
				1,
				Vector2f(0.5,0.5));
			Message2 = new UIText(
				nullptr,
				"Level will be restarted in a few seconds", 
				50u,
				DEFAULT_POSITION,
				1,
				Vector2f(0.5,0.5));

			Message->SetColor(Color(255U, 255U, 255U, 0U));
			Message2->SetColor(Color(255U, 255U, 255U, 0U));
			Message->SetLocalPosition(Vector2f(-Message->GetPixelSize().x * 0.5, -100));
			Message2->SetLocalPosition(Vector2f(-Message2->GetPixelSize().x * 0.5, 0));

			Stage = LoseMessageStage::Appearing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::LoseScript::LoseMessageStage::Appearing:
	{
		if (time < MessageShowingTime) {

			float diff = time - MessageAppearingTime;
			Color clr =	Message->GetColor();
			float transparency = diff / MessageAppearingDeltaTime;
			Message->SetColor(Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255)));
			Message2->SetColor(Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255)));
		}
		else {

			Color clr = Message->GetColor();
			Message->SetColor(Color(clr.r, clr.g, clr.b));
			Message2->SetColor(Color(clr.r, clr.g, clr.b));
			Stage = LoseMessageStage::Showing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::LoseScript::LoseMessageStage::Showing: 
	{
		if (time >= TransitTime) {

			delete Message;
			delete Message2;
			Engine::ReqToSetMode_LevelDeser();
			delete this;
		}
		break;
	}
	default:
		break;
	}
}