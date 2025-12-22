
#include <LoseScript.h>
#include <Engine.h>
#include <GameVisualEffects.h>
#include <InputHandlers.h>

using namespace KrostganEngine::GameTransitions;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

LoseScript::LoseScript()
	:TransitTime(Engine::GetGlobalConsts().LoseMsg_TransitTime),
	MessageAppearingTime(Engine::GetGlobalConsts().LoseMsg_AppearingTime),
	MessageShowingTime(Engine::GetGlobalConsts().LoseMsg_ShowingTime),
	MessageAppearingDeltaTime(MessageShowingTime - MessageAppearingTime) {

	//PlayerInputManager::GetInstance().Clear();
	GroupSelectionSystem::Clear();
	auto locker=new DummyLockerHandler();
	locker->StartHandling();
	LostTimer.restart();
	UserInterfaceLoader::UnloadCurrent();
}

void LoseScript::RenderGraphicAction(RenderWindow& window) {

	float time = LostTimer.getElapsedTime().asSeconds();
	switch (Stage)
	{
	case KrostganEngine::GameTransitions::LoseScript::LoseMessageStage::Hide:
	{
		if (time >= MessageAppearingTime) {

			UserInterfaceLoader::Load_LoseMessage();
			auto beg = UserInterfaceManager::GetRoot().GetChildrenBegin();
			auto end = UserInterfaceManager::GetRoot().GetChildrenAfterEnd();
			IColoredObject* el = nullptr;
			TransparencyVisEff_MRes* eff = nullptr;
			for (;beg != end;++beg) {
				el = dynamic_cast<IColoredObject*>(*beg);
				if (el != nullptr) {

					eff = new TransparencyVisEff_MRes(
						TransparencyVisEff::GetEffectType(TransparencyEffectType::Highlight, TransparencyEffectType::Linear),
						MessageAppearingDeltaTime, 
						*el);
					el->AddEffect(*eff);
					eff->ResetEffect();
				}
			}

			Stage = LoseMessageStage::Appearing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::LoseScript::LoseMessageStage::Appearing:
	{
		if (time >= MessageShowingTime) {
			Stage = LoseMessageStage::Showing;
		}
		break;
	}
	case KrostganEngine::GameTransitions::LoseScript::LoseMessageStage::Showing: 
	{
		if (time >= TransitTime) {

			Engine::ReqToSetMode_LevelDeser();
			delete this;
		}
		break;
	}
	default:
		break;
	}
}