
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
			stats.RestoreHealth();
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

			Message = new TextBlock("Victory. The enemy hero is eliminated.", 50U);
			Message2 = new TextBlock("Level will be restarted in a few seconds", 50u);
			Vector2u screenSize = Engine::GetScreenSize();

			Rect bounds = Message->text.getGlobalBounds();
			Vector2f center = Vector2f(bounds.left + 0.5f * bounds.width, bounds.top + bounds.height * 0.5f);
			Message->text.setOrigin(center);
			Message->ScreenPosition = Vector2f(((float)screenSize.x) / 2, ((float)screenSize.y) / 2);
			Message->text.setFillColor(Color(255U, 255U, 255U, 0U));

			bounds = Message2->text.getGlobalBounds();
			center = Vector2f(bounds.left + 0.5f * bounds.width, bounds.top + bounds.height + 0.5f);
			Message2->text.setOrigin(center);
			Message2->ScreenPosition = Vector2f(((float)screenSize.x) / 2, ((float)screenSize.y) / 2 + 100);
			Message2->text.setFillColor(Color(255U, 255U, 255U, 0U));

			Stage = WinMessageStage::Appearing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::WinScript::WinMessageStage::Appearing:
	{
		if (time < MessageShowingTime) {

			float diff = time - MessageAppearingTime;
			Color clr = Message->text.getFillColor();
			float transparency = diff / MessageAppearingDeltaTime;
			Message->text.setFillColor(Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255)));
			Message2->text.setFillColor(Color(clr.r, clr.g, clr.b, (Uint8)(transparency * 255)));
		}
		else {

			Color clr = Message->text.getFillColor();
			Message->text.setFillColor(Color(clr.r, clr.g, clr.b));
			Message2->text.setFillColor(Color(clr.r, clr.g, clr.b));
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