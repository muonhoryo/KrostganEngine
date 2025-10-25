
#include <WinScript.h>
#include <Engine.h>
#include <EntitiesObserver.h>
#include <CoreGameObjects.h>

using namespace KrostganEngine::GameTransitions;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

WinScript::WinScript()
	:TransitTime(Engine::GetGlobalConsts().LoseMsg_TransitTime),
	MessageAppearingTime(Engine::GetGlobalConsts().LoseMsg_AppearingTime),
	MessageShowingTime(Engine::GetGlobalConsts().LoseMsg_ShowingTime),
	MessageAppearingDeltaTime(MessageShowingTime - MessageAppearingTime) {

	EntitiesCtrlInputHandler::GetInstance()->TurnOff();
	LostTimer.restart();
	auto beg=EntitiesObserver::GetBeginIter();
	auto end = EntitiesObserver::GetAfterEndIter();
	HeroObject* hero = nullptr;
	for (;beg != end;++beg) {
		hero = dynamic_cast<HeroObject*>(*beg);
		if (hero != nullptr && hero->GetFraction() == Fraction::Player)
		{
			auto& stats = hero->GetBattleStats();
			stats.SetMaxHP(1000000);
			hero->GetHPModule().RestoreHealth();
			break;
		}
	}
}

void WinScript::RenderGraphic(RenderWindow& window) {

	float time = LostTimer.getElapsedTime().asSeconds();
	switch (Stage)
	{
	case KrostganEngine::GameTransitions::WinScript::WinMessageStage::Hide:
	{
		if (time >= MessageAppearingTime) {


			Message = new UIText(
				nullptr,
				"Victory. The enemy hero is eliminated.",
				50u,
				DEFAULT_POSITION,
				1,
				Vector2f(0.5, 0.5));
			Message2 = new UIText(
				nullptr,
				"Level will be restarted in a few seconds",
				50u,
				DEFAULT_POSITION,
				1,
				Vector2f(0.5, 0.5));

			Message->SetColor(Color(255U, 255U, 255U, 0U));
			Message2->SetColor(Color(255U, 255U, 255U, 0U));
			Message->SetLocalPosition(Vector2f(-Message->GetGlobalUISize().x * 0.5, -100));
			Message2->SetLocalPosition(Vector2f(-Message2->GetGlobalUISize().x * 0.5, 0));

			Stage = WinMessageStage::Appearing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::WinScript::WinMessageStage::Appearing:
	{
		if (time < MessageShowingTime) {

			float diff = time - MessageAppearingTime;
			Color clr = Message->GetColor();
			float transparency = diff / MessageAppearingDeltaTime;
			Message->SetColor(Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255)));
			Message2->SetColor(Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255)));
		}
		else {

			Color clr = Message->GetColor();
			Message->SetColor(Color(clr.r, clr.g, clr.b));
			Message2->SetColor(Color(clr.r, clr.g, clr.b));
			Stage = WinMessageStage::Showing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::WinScript::WinMessageStage::Showing:
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