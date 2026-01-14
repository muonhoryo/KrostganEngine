
#include <GameEffectsSystem.h>
#include <CollectionsExts.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

IGameEffTarget::IGameEffTarget() {

}
IGameEffTarget::~IGameEffTarget() {

	for (auto eff : AppliedGameEffects) {

		RemoveGameEffEventHan.Execute(*eff);
		delete eff;
	}
}

void IGameEffTarget::AddGameEff(ComposeGameEffect& eff) {

	auto predicate = CatalogObject::Predicate_ByID_n_SubID_ref<ComposeGameEffect>(eff.GetCatalogID(), eff.GetSubcatalogID());
	auto effInColl = CollectionsExts::Get(AppliedGameEffects, predicate);
	if (effInColl == nullptr) {
		AppliedGameEffects.push_front(&eff);
		eff.OnApplyToTarget(*this);
		eff.SourcesCount = 1;
		AddGameEffEventHan.Execute(eff);
	}
	else {
		if (eff.IsStackable) {

			AppliedGameEffects.push_front(&eff);
			eff.OnApplyToTarget(*this);
			AddGameEffEventHan.Execute(eff);
		}
		else {

			(*effInColl)->SourcesCount += 1;
		}
	}
}

void IGameEffTarget::RemoveGameEff(ComposeGameEffect& eff) {

	if (eff.IsStackable) {

		CollectionsExts::Remove(AppliedGameEffects, &eff);
		RemoveGameEffEventHan.Execute(eff);
		delete& eff;
	}
	else {

		RemoveGameEffByID(eff.GetCatalogID(), eff.GetSubcatalogID());
	}
}

void IGameEffTarget::RemoveGameEffByID(size_t catalogID, std::byte subCatalogID) {

	auto predicate = CatalogObject::Predicate_ByID_n_SubID_ref<ComposeGameEffect>(catalogID, subCatalogID);
	auto effInColl = *CollectionsExts::Get(AppliedGameEffects, predicate);

	if (effInColl->SourcesCount <= 1) {
		CollectionsExts::Remove(AppliedGameEffects, effInColl);
		effInColl->OnRemoveFromTarget(*this);
		RemoveGameEffEventHan.Execute(*effInColl);
		delete effInColl;
	}
	else {
		effInColl->SourcesCount--;
	}
}
void IGameEffTarget::RemoveGameEffByID(size_t catalogID) {
	RemoveGameEffByID(catalogID, (std::byte)0);
}